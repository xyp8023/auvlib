/* Copyright 2018 Nils Bore (nbore@kth.se)
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <data_tools/all_data.h>

#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>

using namespace std_data;
using namespace all_data;

namespace py = pybind11;

PYBIND11_MODULE(all_data, m) {
    m.doc() = "Basic utilities for working with the .all file format"; // optional module docstring

    py::class_<all_mbes_ping>(m, "all_mbes_ping", "Class for the all multibeam type")
        .def(py::init<>())
        .def_readwrite("id_", &all_mbes_ping::id_, "Sequential ID of measurement")
        .def_readwrite("time_string_", &all_mbes_ping::time_string_, "Readable date of measurement")
        .def_readwrite("time_stamp_", &all_mbes_ping::time_stamp_, "UNIX timestamp")
        .def_readwrite("heading_", &all_mbes_ping::heading_, "Radian yaw in ENU coordinates")
        .def_readwrite("sound_vel_", &all_mbes_ping::sound_vel_, "Sound velocity")
        .def_readwrite("transducer_depth_", &all_mbes_ping::transducer_depth_, "Depth of sensor")
        .def_readwrite("reflectivities", &all_mbes_ping::reflectivities, "Return reflectivities")
        .def_readwrite("beams", &all_mbes_ping::beams, "Positions of hist in sensor coordinates")
        .def_readwrite("first_in_file_", &all_mbes_ping::first_in_file_, "Is first measurement in file?")
        .def_static("parse_file", &parse_file_from_str<all_mbes_ping>, "Parse all_mbes_ping from .all file")
        .def_static("parse_folder", &parse_folder_from_str<all_mbes_ping>, "Parse all_mbes_ping from folder of .all files")
        .def_static("read_data", &read_data_from_str<all_mbes_ping::PingsT>, "Read all_mbes_ping::PingsT from .cereal file");

    py::class_<all_nav_entry>(m, "all_nav_entry", "Class for the all nav entry")
        .def(py::init<>())
        .def_readwrite("id_", &all_nav_entry::id_, "Sequential ID of measurement")
        .def_readwrite("time_string_", &all_nav_entry::time_string_, "Readable date of measurement")
        .def_readwrite("time_stamp_", &all_nav_entry::time_stamp_, "UNIX timestamp")
        .def_readwrite("lat_", &all_nav_entry::lat_, "Latitude")
        .def_readwrite("long_", &all_nav_entry::long_, "Longitude")
        .def_readwrite("depth_", &all_nav_entry::depth_, "Depth")
        .def_readwrite("heading_", &all_nav_entry::heading_, "Radian yaw in ENU coordinates")
        .def_readwrite("course_over_ground_", &all_nav_entry::course_over_ground_, "TODO")
        .def_readwrite("first_in_file_", &all_nav_entry::first_in_file_, "Is first measurement in file?")
        .def_static("parse_file", &parse_file_from_str<all_nav_entry>, "Parse all_nav_entry from .all file")
        .def_static("parse_folder", &parse_folder_from_str<all_nav_entry>, "Parse all_nav_entry from folder of .all files")
        .def_static("read_data", &read_data_from_str<all_nav_entry::EntriesT>, "Read all_nav_entry::EntriesT from .cereal file");

    py::class_<all_nav_depth>(m, "all_nav_depth", "Class for the all nav depth entry")
        .def(py::init<>())
        .def_readwrite("id_", &all_nav_depth::id_, "Sequential ID of measurement")
        .def_readwrite("time_string_", &all_nav_depth::time_string_, "Readable date of measurement")
        .def_readwrite("time_stamp_", &all_nav_depth::time_stamp_, "UNIX timestamp")
        .def_readwrite("height", &all_nav_depth::height, "Height")
        .def_readwrite("height_type", &all_nav_depth::height_type, "TODO")
        .def_readwrite("first_in_file_", &all_nav_depth::first_in_file_, "Is first measurement in file?")
        .def_static("parse_file", &parse_file_from_str<all_nav_depth>, "Parse all_nav_depth from .all file")
        .def_static("parse_folder", &parse_folder_from_str<all_nav_depth>, "Parse all_nav_depth from folder of .all files")
        .def_static("read_data", &read_data_from_str<all_nav_depth::EntriesT>, "Read all_nav_depth::EntriesT from .cereal file");

    py::class_<all_nav_attitude_sample>(m, "all_nav_attitude_sample", "Class for the all nav attitude sample entry")
        .def(py::init<>())
        .def_readwrite("ms_since_start", &all_nav_attitude_sample::ms_since_start, "Milliseconds since start of measurements")
        .def_readwrite("roll", &all_nav_attitude_sample::roll, "Radian roll in ENU coordinates")
        .def_readwrite("pitch", &all_nav_attitude_sample::pitch, "Radian pitch in ENU coordinates")
        .def_readwrite("heading", &all_nav_attitude_sample::heading, "Radian yaw in ENU coordinates")
        .def_readwrite("heave", &all_nav_attitude_sample::heave, "Heave");

    py::class_<all_nav_attitude>(m, "all_nav_attitude", "Class for the all nav attitude entry")
        .def(py::init<>())
        .def_readwrite("id_", &all_nav_attitude::id_, "Sequential ID of measurement")
        .def_readwrite("time_string_", &all_nav_attitude::time_string_, "Readable date of measurement")
        .def_readwrite("time_stamp_", &all_nav_attitude::time_stamp_, "UNIX timestamp")
        .def_readwrite("first_in_file_", &all_nav_attitude::first_in_file_, "Is first measurement in file?")
        .def_readwrite("samples", &all_nav_attitude::samples, "The measurements")
        .def_static("parse_file", &parse_file_from_str<all_nav_attitude>, "Parse all_nav_attitude from .all file")
        .def_static("parse_folder", &parse_folder_from_str<all_nav_attitude>, "Parse all_nav_attitude from folder of .all files")
        .def_static("read_data", &read_data_from_str<all_nav_attitude::EntriesT>, "Read all_nav_attitude::EntriesT from .cereal file");

    py::class_<all_echosounder_depth>(m, "all_echosounder_depth", "Class for the all single-beam echosounder depth")
        .def(py::init<>())
        .def_readwrite("id_", &all_echosounder_depth::id_, "Sequential ID of measurement")
        .def_readwrite("time_string_", &all_echosounder_depth::time_string_, "Readable date of measurement")
        .def_readwrite("time_stamp_", &all_echosounder_depth::time_stamp_, "UNIX timestamp")
        .def_readwrite("depth_", &all_echosounder_depth::depth_, "Depth")
        .def_readwrite("first_in_file_", &all_echosounder_depth::first_in_file_, "Is first measurement in file?")
        .def_static("parse_file", &parse_file_from_str<all_echosounder_depth>, "Parse all_echosounder_depth from .all file")
        .def_static("parse_folder", &parse_folder_from_str<all_echosounder_depth>, "Parse all_echosounder_depth from folder of .all files")
        .def_static("read_data", &read_data_from_str<all_echosounder_depth::EntriesT>, "Read all_echosounder_depth::EntriesT from .cereal file");

    m.def("write_data", &write_data_from_str<all_mbes_ping::PingsT>, "Write all_mbes_ping::PingsT to .cereal file");
    m.def("write_data", &write_data_from_str<all_nav_entry::EntriesT>, "Write all_nav_entry::EntriesT to .cereal file");
    m.def("write_data", &write_data_from_str<all_nav_depth::EntriesT>, "Write all_nav_depth::EntriesT to .cereal file");
    m.def("write_data", &write_data_from_str<all_nav_attitude::EntriesT>, "Write all_nav_attitude::EntriesT to .cereal file");
    m.def("write_data", &write_data_from_str<all_echosounder_depth::EntriesT>, "Write all_echosounder_depth::EntriesT to .cereal file");
    //m.def("convert_matched_entries", (all_mbes_ping::PingsT (*)(all_mbes_ping::PingsT&, all_nav_entry::EntriesT&) ) &convert_matched_entries, "Matches xtf_sss_ping::PingsT and csv_nav_entry::EntriesT and assign pos data to pings");
    m.def("convert_matched_entries", &convert_matched_entries, "Matches all_mbes_ping::PingsT and all_nav_entry::EntriesT and assign pos data to pings");
    m.def("match_attitude", &match_attitude, "Match mbes_ping::PingsT and all_nav_attitude::EntriesT and assign attitude data to pings");
    m.def("convert_sound_speeds", &convert_sound_speeds, "Convert all_mbes_ping::PingsT to csv_asvp_sound_speed::EntriesT");
    m.def("convert_attitudes", &convert_attitudes, "Convert all_nav_attitude::EntriesT to std_data::attitude_entry::EntriesT");

    py::class_<StreamParser>(m, "StreamParser", "Class for parsing all data directly from a network stream")
        // Methods inherited from MapImageDraper:
        .def(py::init<>())
        .def("parse_packet", &StreamParser::parse_packet, "Parse a string containing the packet load, and call the set callbacks with the corresponding data types")
        .def("set_mbes_callback", &StreamParser::set_mbes_callback, "Callback to call when encountering all_mbes_ping packets")
        .def("set_nav_entry_callback", &StreamParser::set_nav_entry_callback, "Callback to call when encountering all_nav_entry packets");
}
