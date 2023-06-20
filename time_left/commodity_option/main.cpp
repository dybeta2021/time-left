//
// Created by 稻草人 on 2023/6/16.
//

#include "load_cal_dates.h"
#include "time_left.h"

int main() {
    {
        const std::vector<std::string> day_cal_dates = {"2023-06-15", "2023-06-16", "2023-06-19", "2023-06-20", "2023-06-21", "2023-06-23", "2023-06-26"};
        std::cout << "day_count current_date:" << DateLeft::GetDayCurrentDate() << std::endl;
        std::cout << "night_count current_date:" << DateLeft::GetNightCurrentDate() << std::endl;
        std::cout << "day_left:" << DateLeft(day_cal_dates).GetDayLeft(DateLeft::GetDayCurrentDate(), "2023-06-21") << std::endl;
        std::cout << "night_left:" << DateLeft(day_cal_dates).GetDayLeft(DateLeft::GetNightCurrentDate(), "2023-06-21") << std::endl;
    }

    {
        auto day_time_left = DayTimeLeft("09:00:00", "10:15:00", "10:30:00", "11:30:00", "13:30:00", "15:00:00");
        std::cout << "day_time_left:" << day_time_left.GetTimeLeft() << ", total_time:" << day_time_left.GetTotalTime() << std::endl;

        auto night_time_left = NightTimeLeft("21:00:00", "23:00:00");
        std::cout << "night_time_left:" << night_time_left.GetTimeLeft() << ", total_time:" << night_time_left.GetTotalTime() << std::endl;
    }

    {
        std::vector<std::string> file_name{};
        file_name.emplace_back("future_day_transaction_calendar_2019.json");
        file_name.emplace_back("future_day_transaction_calendar_2020.json");
        file_name.emplace_back("future_day_transaction_calendar_2021.json");
        file_name.emplace_back("future_day_transaction_calendar_2022.json");
        file_name.emplace_back("future_day_transaction_calendar_2023.json");
        file_name.emplace_back("future_day_transaction_calendar_2024.json");
        file_name.emplace_back("future_day_transaction_calendar_2025.json");
        const auto day_cal_dates = concat_dates_from_files(file_name);

        file_name.clear();
        file_name.emplace_back("future_night_transaction_calendar_2019.json");
        file_name.emplace_back("future_night_transaction_calendar_2020.json");
        file_name.emplace_back("future_night_transaction_calendar_2021.json");
        file_name.emplace_back("future_night_transaction_calendar_2022.json");
        file_name.emplace_back("future_night_transaction_calendar_2023.json");
        file_name.emplace_back("future_night_transaction_calendar_2024.json");
        file_name.emplace_back("future_night_transaction_calendar_2025.json");
        const auto night_cal_dates = concat_dates_from_files(file_name);

        auto time_left = TimeLeft(day_cal_dates,
                                  night_cal_dates,
                                  244,
                                  237,
                                  "09:00:00",
                                  "10:15:00",
                                  "10:30:00",
                                  "11:30:00",
                                  "13:30:00",
                                  "15:00:00",
                                  "21:00:00",
                                  "23:00:00",
                                  "2023-07-01");
        std::cout << time_left.GetTimeLeft() << std::endl;
    }

    return 0;
}
