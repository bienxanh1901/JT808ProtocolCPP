#ifndef EXTRALOCATIONINFORMATIONSCHEMA_H
#define EXTRALOCATIONINFORMATIONSCHEMA_H

#include "nlohmann/json.hpp"
namespace Schema {

static nlohmann::json ExtraLocationInformationSchema = R"(
{
    "type": "object",
    "properties": {
        "mileage": {
            "description": "Mileage",
            "type": "number"
        },
        "fuel_meter": {
            "description": "Fuel Meter",
            "type": "number"
        },
        "speed": {
            "description": "Speed from Driving Record Function",
            "type": "number"
        },
        "alarm_id": {
            "description": "ID of Alarm Events Needing Manual Confirmation",
            "type": "number"
        },
        "overspeed_alarm": {
            "description": "Overspeed Alarm Additional Information",
            "type": "object",
            "properties": {
                "type": {
                    "description": "Location Type",
                    "type": "number"
                },
                "id": {
                    "description": "Area or Segment ID",
                    "type": "number"
                }
            },
            "required": ["type"]
        },
        "in_out_alarm": {
            "description": "Entry/Exit Area/Route Alarm Additional Information",
            "type": "object",
            "properties": {
                "type": {
                    "description": "Location Type",
                    "type": "number"
                },
                "id": {
                    "description": "Area or Segment ID",
                    "type": "number"
                },
                "direction": {
                    "description": "Direction",
                    "type": "number"
                }
            },
            "required": ["type", "id", "direction"]
        },
        "path_time_alarm": {
            "description": "Route Travel Time Too Short/Too Long Alarm Additional Information",
            "type": "object",
            "properties": {
                "id": {
                    "description": "Segment ID",
                    "type": "number"
                },
                "time": {
                    "description": "Route Travel Time",
                    "type": "number"
                },
                "result": {
                    "description": "Result",
                    "type": "number"
                }
            },
            "required": ["id", "time", "result"]
        },
        "extended_vehicle_signal_status": {
            "description": "Extended Vehicle Signal Status Bits",
            "type": "object",
            "properties": {
                "low_beam": {
                    "description": "Low beam signal",
                    "type": "number"
                },
                "high_beam": {
                    "description": "High beam signal",
                    "type": "number"
                },
                "right_turn": {
                    "description": "Right Turn Signal",
                    "type": "number"
                },
                "left_turn": {
                    "description": "Left Turn Signal",
                    "type": "number"
                },
                "brake": {
                    "description": "Brake Signal",
                    "type": "number"
                },
                "reverse": {
                    "description": "Reverse Signal",
                    "type": "number"
                },
                "fog": {
                    "description": "Fog Light Signal",
                    "type": "number"
                },
                "side_marker": {
                    "description": "Side Marker",
                    "type": "number"
                },
                "horn": {
                    "description": "Horn Status",
                    "type": "number"
                },
                "air_conditioner": {
                    "description": "Air Conditioner Status",
                    "type": "number"
                },
                "neutral": {
                    "description": "Neutral Signal",
                    "type": "number"
                },
                "retarder": {
                    "description": "Retarder Working",
                    "type": "number"
                },
                "abs": {
                    "description": "ABS Working",
                    "type": "number"
                },
                "heater": {
                    "description": "Heater Working",
                    "type": "number"
                },
                "cluth": {
                    "description": "Clutch Status",
                    "type": "number"
                }
            },
            "required": [
                "high_beam", "low_beam", "right_turn", "left_turn", "brake",
                "reverse", "fog", "side_marker", "horn", "air_conditioner",
                "neutral", "retarder", "abs", "heater", "cluth"
            ]
        },
        "io_status": {
            "description": "IO Status Bits",
            "type": "object",
            "properties": {
                "deep_sleep": {
                    "description": "Deep Sleep Status",
                    "type": "number"
                },
                "sleep": {
                    "description": "Sleep Status",
                    "type": "number"
                }
            },
            "required": ["deep_sleep", "sleep"]
        },
        "analog": {
            "description": "Analog",
            "type": "object",
            "properties": {
                "ad0": {
                    "description": "Analog 0",
                    "type": "number"
                },
                "ad1": {
                    "description": "Analog 1",
                    "type": "number"
                }
            },
            "required": ["ad0", "ad1"]
        },
        "rssi": {
            "description": "Wireless Communication Network Signal Strength",
            "type": "number"
        },
        "gnss_sat_num": {
            "description": "GNSS Satellite Count",
            "type": "number"
        },
        "custom": {
            "description": "Custom Information",
            "type": "array",
            "items": {
                "type": "object",
                "properties": {
                    "id": {
                        "description": "Extra ID",
                        "type": "number"
                    },
                    "length": {
                        "description": "Length of Data",
                        "type": "number"
                    },
                    "data": {
                        "description": "Data Content",
                        "type": "array",
                        "items": {
                            "type": "number"
                        }
                    }
                }
            }
        }
    }
}

)"_json;

}
#endif // EXTRALOCATIONINFORMATIONSCHEMA_H
