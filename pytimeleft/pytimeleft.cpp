//
// Created by 稻草人 on 2023/6/16.
//
#pragma warning(disable : 4996)
#include "commodity_option.h"
#include "pybind11/pybind11.h"
#include "pybind11/stl.h"
#include "stock_option.h"

namespace py = pybind11;


PYBIND11_MODULE(pytimeleft, m) {
    py::class_<stock_option::TimeLeft>(m, "StockOptionTimeLeft")
            .def(py::init<const std::vector<std::string> &,
                          const int &,
                          const std::string &,
                          const std::string &,
                          const std::string &,
                          const std::string &,
                          const std::string &>(),
                 py::arg("cal_dates"),
                 py::arg("date_num_in_year"),
                 py::arg("am_start"),
                 py::arg("am_end"),
                 py::arg("pm_start"),
                 py::arg("pm_end"),
                 py::arg("expiry_date"))
            .def("GetTimeLeft", &stock_option::TimeLeft::GetTimeLeft)
            .def("GetTotalTimeOneDay", &stock_option::TimeLeft::GetTotalTimeOneDay);

    py::class_<commodity_option::TimeLeft>(m, "CommodityOptionTimeLeft")
            .def(py::init<const std::vector<std::string> &,
                          const std::vector<std::string> &,
                          const int &,
                          const int &,
                          const std::string &,
                          const std::string &,
                          const std::string &,
                          const std::string &,
                          const std::string &,
                          const std::string &,
                          const std::string &,
                          const std::string &,
                          const std::string &>(),
                 py::arg("day_cal_dates"),
                 py::arg("night_cal_dates"),
                 py::arg("day_num_in_year"),
                 py::arg("night_num_in_year"),
                 py::arg("am_start"),
                 py::arg("am_end"),
                 py::arg("mid_start"),
                 py::arg("mid_end"),
                 py::arg("pm_start"),
                 py::arg("pm_end"),
                 py::arg("night_start"),
                 py::arg("night_end"),
                 py::arg("expiry_date"))
            .def("GetTimeLeft", &commodity_option::TimeLeft::GetTimeLeft)
            .def("GetTotalTimeOneDay", &commodity_option::TimeLeft::GetTotalTimeOneDay)
            .def("GetDayTimeOneDay", &commodity_option::TimeLeft::GetDayTimeOneDay)
            .def("GetNightTimeOneDay", &commodity_option::TimeLeft::GetNightTimeOneDay);
}
