#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Project  : test 
# @File     : test.py 
# @Author   : Gavin
# @Time     : 2023/6/21 8:42
# @Desc     :

from json import load
from os import listdir
from os import sep, getcwd

from numpy import unique, ndarray
from pandas import concat, read_excel, DataFrame
from pytimeleft import CommodityOptionTimeLeft, StockOptionTimeLeftV2, StockOptionTimeLeft


def read_excel_file(path: str = None) -> DataFrame:
    """

    :param path:
    :return:
    """
    if path is None:
        path = getcwd() + sep + r"access" + sep + r"time_table" + sep + r"商品交易时间20230103.xlsx"
    data = read_excel(io=path)

    time_table = []
    for i in range(data.shape[0]):
        row = data.iloc[i]
        row["symbol"] = row["合约代码"].lower()
        row["type"] = "option" if "期权" in row["品种"] else "future"
        time_table.append(row)
    time_table = concat(time_table, axis=1, sort=True).T
    time_table = time_table.fillna("None")
    return time_table


def get_cal_dates(path: str = None) -> (ndarray, ndarray):
    """
    获取交易日历

    :param path:
    :return:
    """
    if path is None:
        path = getcwd() + sep + r"access" + sep + r"calendar"

    file_list = [i for i in listdir(path) if "future_day_transaction_calendar_" in i]
    day_cal_dates = []
    for file_name in file_list:
        with open(path + sep + file_name) as fp:
            day_cal_dates += load(fp)
    day_cal_dates = unique(day_cal_dates)

    file_list = [i for i in listdir(path) if "future_night_transaction_calendar_" in i]
    night_cal_dates = []
    for file_name in file_list:
        with open(path + sep + file_name) as fp:
            night_cal_dates += load(fp)
    night_cal_dates = unique(night_cal_dates)
    return day_cal_dates, night_cal_dates


class TimeLeft(object):
    def __init__(self, config: dict, expiry_date: str):
        if config["日盘交易时间"] == "上午：09:00-10:15 10:30-11:30 下午：13:30-15:00" and config[
            "夜盘交易时间"] == "21:00-次日1:00":
            self.time_left = CommodityOptionTimeLeft(
                day_cal_dates=day_cal_dates,
                night_cal_dates=night_cal_dates,
                day_num_in_year=_day_trading_num,
                night_num_in_year=_night_trading_num,
                am_start="09:00:00",
                am_end="10:15:00",
                mid_start="10:30:00",
                mid_end="11:30:00",
                pm_start="13:30:00",
                pm_end="15:00:00",
                night_start="21:00:00",
                night_end="01:00:00",
                expiry_date=expiry_date)

        elif config["日盘交易时间"] == "上午：09:00-10:15 10:30-11:30 下午：13:30-15:00" and config[
            "夜盘交易时间"] == "21:00-次日2:30":
            self.time_left = CommodityOptionTimeLeft(
                day_cal_dates=day_cal_dates,
                night_cal_dates=night_cal_dates,
                day_num_in_year=_day_trading_num,
                night_num_in_year=_night_trading_num,
                am_start="09:00:00",
                am_end="10:15:00",
                mid_start="10:30:00",
                mid_end="11:30:00",
                pm_start="13:30:00",
                pm_end="15:00:00",
                night_start="21:00:00",
                night_end="02:30:00",
                expiry_date=expiry_date)

        elif config["日盘交易时间"] == "上午：09:00-10:15 10:30-11:30 下午：13:30-15:00" and config[
            "夜盘交易时间"] == "21:00-23:00":
            self.time_left = CommodityOptionTimeLeft(
                day_cal_dates=day_cal_dates,
                night_cal_dates=night_cal_dates,
                day_num_in_year=_day_trading_num,
                night_num_in_year=_night_trading_num,
                am_start="09:00:00",
                am_end="10:15:00",
                mid_start="10:30:00",
                mid_end="11:30:00",
                pm_start="13:30:00",
                pm_end="15:00:00",
                night_start="21:00:00",
                night_end="23:00:00",
                expiry_date=expiry_date)

        elif config["日盘交易时间"] == "上午：09:00-10:15 10:30-11:30 下午：13:30-15:00" and config[
            "夜盘交易时间"] == "无":
            self.time_left = StockOptionTimeLeftV2(
                cal_dates=day_cal_dates,
                date_num_in_year=_day_trading_num,
                am_start="09:00:00",
                am_end="10:15:00",
                mid_start="10:30:00",
                mid_end="11:30:00",
                pm_start="13:30:00",
                pm_end="15:00:00",
                expiry_date=expiry_date)

        elif config["日盘交易时间"] == "上午：09:30-11:30 下午：13:00-15:00" and config[
            "夜盘交易时间"] == "无":
            self.time_left = StockOptionTimeLeft(
                cal_dates=day_cal_dates,
                date_num_in_year=_day_trading_num,
                am_start="09:30:00",
                am_end="11:30:00",
                pm_start="13:00:00",
                pm_end="15:00:00",
                expiry_date=expiry_date)

        elif config["日盘交易时间"] == "上午：09:30-11:30 下午：13:00-15:15" and config[
            "夜盘交易时间"] == "无":
            self.time_left = StockOptionTimeLeft(
                cal_dates=day_cal_dates,
                date_num_in_year=_day_trading_num,
                am_start="09:30:00",
                am_end="11:30:00",
                pm_start="13:00:00",
                pm_end="15:15:00",
                expiry_date=expiry_date)
        else:
            print(config)
            raise ValueError

    def get_time_left(self):
        return self.time_left.GetTimeLeft()

    def get_total_time_one_day(self):
        return self.time_left.GetTotalTimeOneDay()


if __name__ == "__main__":
    # 商品期权不同的交易时间调整
    time_table = read_excel_file()
    _day_trading_num = 244
    _night_trading_num = 237

    day_cal_dates, night_cal_dates = get_cal_dates()

    time_table = read_excel_file()
    for config in time_table.to_dict(orient="records"):
        print(config)
        print(TimeLeft(config=config, expiry_date="2023-06-27").get_time_left())
