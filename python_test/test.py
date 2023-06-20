from json import load
from os import getcwd, listdir, sep

from numpy import unique
from pytimeleft import StockOptionTimeLeft

path = getcwd() + sep + r"access" + sep + r"calendar"
file_list = listdir(path)
file_list = [i for i in file_list if "transaction_calendar_" in i and "future_" not in i]

cal_dates = []
for file_name in file_list:
    with open(path + sep + file_name) as fp:
        cal_dates += load(fp)
cal_dates = unique(cal_dates)

time_left = StockOptionTimeLeft(cal_dates=cal_dates,
                                date_num_in_year=244,
                                am_start="09:30:00",
                                am_end="11:30:00",
                                pm_start="13:00:00",
                                pm_end="15:00:00",
                                expiry_date="2023-07-01")
print(time_left.GetTimeLeft())
