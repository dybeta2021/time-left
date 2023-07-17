#pragma once
#include <algorithm>
#include <fstream>
#include <nlohmann/json.hpp>
#include <set>
#include <string>
#include <vector>

// 一个辅助函数，用于从JSON文件中读取日期并添加到vector和set中
void read_dates_from_file(const std::string &file_name, std::vector<std::string> &dates, std::set<std::string> &dates_set) {
    // 打开文件
    std::ifstream file_input(file_name);
    // 创建一个JSON对象
    nlohmann::json json;
    // 从文件中解析JSON
    file_input >> json;
    // 遍历JSON数组
    for (const auto &date: json) {
        // 获取日期字符串
        std::string date_str = date.get<std::string>();
        // 如果日期不在set中，说明是新的日期
        if (dates_set.find(date_str) == dates_set.end()) {
            // 将日期添加到vector和set中
            dates.push_back(date_str);
            dates_set.insert(date_str);
        }
    }
}

// 一个主函数，用于拼接多个JSON文件中的日期为一个vector<string>
std::vector<std::string> concat_dates_from_files(const std::vector<std::string> &file_names) {
    // 创建一个空的vector<string>来存储所有的日期
    std::vector<std::string> dates;
    // 创建一个空的set<string>来去除重复的日期
    std::set<std::string> dates_set;
    // 遍历所有的文件名
    for (const auto &file_name: file_names) {
        // 调用辅助函数，从文件中读取日期并添加到vector和set中
        read_dates_from_file(file_name, dates, dates_set);
    }
    // 对vector进行排序
    std::sort(dates.begin(), dates.end());
    // 返回排序后的vector
    return dates;
}
