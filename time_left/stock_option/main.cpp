//
// Created by 稻草人 on 2023/6/16.
//

#include "load_cal_dates.h"
#include "time_left.h"

int main() {
    std::vector<std::string> file_name{};
    file_name.emplace_back("transaction_calendar_2022.json");
    file_name.emplace_back("transaction_calendar_2023.json");
    file_name.emplace_back("transaction_calendar_2024.json");
    file_name.emplace_back("transaction_calendar_2025.json");
    const auto cal_dates = concat_dates_from_files(file_name);

    {
        auto day_left = DateLeft(cal_dates);
        auto current_date = DateLeft::GetCurrentDate();
        std::cout << "current_date:" << current_date << std::endl;
        std::cout << "day_left:" << day_left.GetDayLeft(current_date, "2023-07-01") << std::endl;
    }

    {
        auto time_left = DatetimeLeft("09:30:00", "11:30:00", "13:00:00", "15:00:00");
        const auto current_time = DatetimeLeft::GetCurrentTime();
        std::cout << "time_left:" << time_left.GetTimeLeft(current_time) << std::endl;
        std::cout << "time_left:" << time_left.GetTimeLeft() << std::endl;
    }

    {
        auto time_left = TimeLeft(cal_dates, 244, "09:30:00", "11:30:00", "13:00:00", "15:00:00", "2023-07-01");
        std::cout << "time_left:" << time_left.GetTimeLeft() << std::endl;
    }

    return 0;
}