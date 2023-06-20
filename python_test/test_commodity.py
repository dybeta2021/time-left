from json import load
from os import getcwd, listdir, sep

from numpy import unique
from pytimeleft import CommodityOptionTimeLeft

path = getcwd() + sep + r"access" + sep + r"calendar"
file_list = listdir(path)

day_cal_dates = []
for file_name in [i for i in file_list if "future_day_transaction_calendar_" in i]:
    with open(path + sep + file_name) as fp:
        day_cal_dates += load(fp)
day_cal_dates = unique(day_cal_dates)

night_cal_dates = []
for file_name in [i for i in file_list if "future_night_transaction_calendar_" in i]:
    with open(path + sep + file_name) as fp:
        night_cal_dates += load(fp)
night_cal_dates = unique(night_cal_dates)

time_left = CommodityOptionTimeLeft(
    day_cal_dates=day_cal_dates,
    night_cal_dates=night_cal_dates,
    day_num_in_year=244,
    night_num_in_year=237,
    am_start="09:00:00",
    am_end="10:15:00",
    mid_start="10:30:00",
    mid_end="11:30:00",
    pm_start="13:30:00",
    pm_end="15:00:00",
    night_start="21:00:00",
    night_end="23:00:00",
    expiry_date="2023-07-01")
print(time_left.GetTimeLeft())
