#include "Initialize.h"

Initialize* Initialize::initialize = nullptr;

Initialize::Initialize(){
    std::ifstream inifile("config.ini");
    inicpp::IniManager _ini("config.ini");

    if (!inifile.good()) {
        _ini["FPS"]["FPS"] = "15";
        _ini["Key"]["KeySmugglingTimer"] = "6";
        _ini["Key"]["KeyKillingTimer"] = "5";
        _ini["View"]["OffsetX"] = "0";
        _ini["View"]["OffsetY"] = "0";
        _ini["SmugglingTimer"]["MaxTime(s)"] = "600";
        _ini["SmugglingTimer"]["Enable"] = "true";
        _ini["KillingTimer"]["MaxTime(s)"] = "30";
        _ini["KillingTimer"]["Enable"] = "true";
    }

    GetValue();

    if (inifile.is_open()) {
        inifile.close();
    }
}

Initialize::~Initialize() {
}

void Initialize::GetValue() {
    std::ifstream inifile("config.ini");
    inicpp::IniManager _ini("config.ini");

    FPS = _ini["FPS"]["FPS"].get<int>();
    KEY_SMUGGLINGTIMER = _ini["Key"]["KeySmugglingTimer"].get<int>();
    KEY_KILLINGTIMER = _ini["Key"]["KeyKillingTimer"].get<int>();
    OFFSET_X = _ini["View"]["OffsetX"].get<int>();
    OFFSET_Y = _ini["View"]["OffsetY"].get<int>();
    MAX_SMUGGLING_TIME = _ini["SmugglingTimer"]["MaxTime(s)"].get<int>();
    ENABLE_SMUGGLING_TIMER = (_ini["SmugglingTimer"]["Enable"].get<std::string>() == "true") ? true : false;
    MAX_KILLING_TIME = _ini["KillingTimer"]["MaxTime(s)"].get<int>();
    ENABLE_KILLING_TIMER = (_ini["KillingTimer"]["Enable"].get<std::string>() == "true") ? true : false;

    if (inifile.is_open()) {
        inifile.close();
    }
}

Initialize* Initialize::getInstance() {
    if (initialize == nullptr) initialize = new Initialize;
    return initialize;
}