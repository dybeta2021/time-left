#pragma once

#include <algorithm>
#include <ctime>
#include <format>
#include <iomanip>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

namespace stock_option {
    class DateLeft {
    private:
        std::vector<std::string> cal_dates_{};

    public:
        // 定义一个函数，用于检查输入数据是否为年-月-日的格式
        static int check_date(const std::string &date) {
            // 使用正则表达式来匹配输入数据的格式
            // 假设年份为四位数字，月份和日期为两位数字，且月份在1到12之间，日期在1到31之间
            static std::regex pattern(R"(\d{4}-(0[1-9]|1[0-2])-(0[1-9]|[12]\d|3[01]))");// 将正则表达式对象声明为静态，避免每次调用函数时重新构造
            // 返回正则表达式是否匹配输入数据
            return std::regex_match(date, pattern) ? 0 : -1;
        }

        static int check_data_vector(const std::vector<std::string> &cal_dates) {// 将参数声明为常量引用，避免拷贝
            for (const auto &s: cal_dates) {                                     // 使用范围for循环，简化代码
                if (check_date(s) != 0) {
                    return -1;
                }
            }
            return 0;// 将返回值放在循环外面，避免多次返回
        }

        // 定义一个比较函数，用于比较两个日期字符串的大小
        static bool compare_date(const std::string &a, const std::string &b) {
            // 假设日期字符串的格式为"yyyy-mm-dd"
            // 可以直接按字典序比较
            return a < b;
        }

        // 定义一个函数，用于对cal_dates进行排序，并返回排序后的vector
        static std::vector<std::string> sort_cal_dates(const std::vector<std::string> &cal_dates) {
            // 创建一个新的vector，用于存储排序后的数据
            std::vector<std::string> sorted_cal_dates = cal_dates;
            // 使用标准库的sort函数，根据compare_date函数的比较规则，对sorted_cal_dates进行升序排序
            std::sort(sorted_cal_dates.begin(), sorted_cal_dates.end(), compare_date);
            // 返回sorted_cal_dates
            return sorted_cal_dates;
        }


        // 定义一个函数，用于计算vector中在指定日期范围内的数据点个数
        static int count_date(const std::vector<std::string> &date_vector, const std::string &start_date,
                              const std::string &end_date) {
            // 使用标准库的upper_bound函数，分别找到第一个大于start_date和第一个大于end_date的迭代器
            auto start_it = std::upper_bound(date_vector.begin(), date_vector.end(), start_date, compare_date);
            auto end_it = std::upper_bound(date_vector.begin(), date_vector.end(), end_date, compare_date);
            // 返回两个迭代器之间的距离，即为所求的个数
            return static_cast<int>(std::distance(start_it, end_it));
        }

    public:
        explicit DateLeft(const std::vector<std::string> &cal_dates) {
            if (check_data_vector(cal_dates) != 0) {
                throw std::invalid_argument("Error date format for cal_dates!");
            }
            cal_dates_ = sort_cal_dates(cal_dates);
        }

        double GetDayLeft(const std::string &current_date, const std::string &expiry_date) {
            if (check_date(current_date)) {
                throw std::invalid_argument("Error date format for current_date!");
            }
            if (check_date(expiry_date)) {
                throw std::invalid_argument("Error date format for expiry_date!");
            }
            const auto day_left = count_date(cal_dates_, current_date, expiry_date);
            return day_left;
        }

        static std::string GetCurrentDate() {
            // 获取当前时间
            time_t now = time(nullptr);
            // 转化为tm结构体
            tm *ltm = localtime(&now);
            // 定义年月日字符串
            std::string date;
            // 定义格式化缓冲区
            char buffer[256];
            // 格式化日期字符串
            strftime(buffer, sizeof(buffer), "%Y-%m-%d", ltm);
            // 赋值给date
            date = buffer;
            // 返回字符串
            return date;
        }
    };


    class DatetimeLeft {
    private:
        std::time_t am_start_{};
        std::time_t am_end_{};
        std::time_t pm_start_{};
        std::time_t pm_end_{};
        int total_time_one_day_{};

    public:
        static auto
        time_to_timestamp(const std::string &datetime_str) {
            std::tm datetime_tm = {};
            std::istringstream datetime_stream(datetime_str);
            datetime_stream >> std::get_time(&datetime_tm, "%H:%M:%S");
            std::time_t now_t = std::time(nullptr);
            std::tm now_tm = *std::localtime(&now_t);
            datetime_tm.tm_year = now_tm.tm_year;
            datetime_tm.tm_mon = now_tm.tm_mon;
            datetime_tm.tm_mday = now_tm.tm_mday;
            std::time_t datetime_t = std::mktime(&datetime_tm);
            return datetime_t;
        }

        /// 返回秒
        /// \param start_t
        /// \param end_t
        /// \return
        static auto get_time_diff(const std::time_t &start_t, const std::time_t &end_t) {
            auto time_diff = std::difftime(end_t, start_t);
            return time_diff;
        }


    public:
        DatetimeLeft(const std::string &am_start, const std::string &am_end, const std::string &pm_start,
                     const std::string &pm_end) {
            am_start_ = time_to_timestamp(am_start);
            am_end_ = time_to_timestamp(am_end);
            pm_start_ = time_to_timestamp(pm_start);
            pm_end_ = time_to_timestamp(pm_end);

            auto am_diff = get_time_diff(am_start_, am_end_);
            auto pm_diff = get_time_diff(pm_start_, pm_end_);
            total_time_one_day_ = static_cast<int>(am_diff + pm_diff);
        }

        [[nodiscard]] auto GetTotalTimeOneDay() const {
            return total_time_one_day_;
        }

        static std::time_t GetCurrentTime() {
            std::time_t now_t = std::time(nullptr);
            return now_t;
        }

        /// 返回单位秒
        [[nodiscard]] auto GetTimeLeft(const std::time_t &now_t) const {
            if (now_t < am_start_) {
                return std::difftime(am_end_, am_start_) + std::difftime(pm_end_, pm_start_);
            } else if (now_t >= am_start_ && now_t < am_end_) {
                return std::difftime(am_end_, now_t) + std::difftime(pm_end_, pm_start_);
            } else if (now_t >= am_end_ && now_t < pm_start_) {
                return std::difftime(pm_end_, pm_start_);
            } else if (now_t >= pm_start_ && now_t < pm_end_) {
                return std::difftime(pm_end_, now_t);
            } else {
                return 0.;
            }
        }

        /// 返回单位日
        /// \return
        [[nodiscard]] auto GetTimeLeft() const {
            std::time_t now_t = GetCurrentTime();
            auto time_left = GetTimeLeft(now_t);
            return time_left / (double) total_time_one_day_;
        }
    };

    class TimeLeft {
    private:
        std::unique_ptr<DatetimeLeft> ptr_datetime_left_;
        std::unique_ptr<DateLeft> ptr_date_left_;
        double date_left_{};
        int date_num_in_year_{};
        bool is_holiday_{};

        /// 返回单位年
        auto get_time_left() {
            if (is_holiday_) {
                return date_left_ / date_num_in_year_;
            }

            auto time_left = ptr_datetime_left_->GetTimeLeft();
            return (time_left + date_left_) / date_num_in_year_;
        }

    public:
        TimeLeft(const std::vector<std::string> &cal_dates,
                 const int &date_num_in_year,
                 const std::string &am_start,
                 const std::string &am_end,
                 const std::string &pm_start,
                 const std::string &pm_end,
                 const std::string &expiry_date) {
            ptr_datetime_left_ = std::make_unique<DatetimeLeft>(am_start, am_end, pm_start, pm_end);
            ptr_date_left_ = std::make_unique<DateLeft>(cal_dates);
            date_num_in_year_ = date_num_in_year;
            date_left_ = ptr_date_left_->GetDayLeft(ptr_date_left_->GetCurrentDate(), expiry_date);

            auto it = std::find(cal_dates.begin(), cal_dates.end(), ptr_date_left_->GetCurrentDate());
            if (it != cal_dates.end()) {
                is_holiday_ = false;
            } else {
                is_holiday_ = true;
            }
        }

        auto GetTotalTimeOneDay() {
            return ptr_datetime_left_->GetTotalTimeOneDay();
        }

        auto GetTimeLeft() {
            const auto time_left = get_time_left();
            return time_left < 1e-6 ? 1e-6 : time_left;
        }
    };
}// namespace stock_option