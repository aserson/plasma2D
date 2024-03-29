#include "Configs.h"

#include <fstream>
#include <iomanip>
#include <iostream>

namespace mhd {
Configs::Configs(const std::filesystem::path& filePath) : _filePath(filePath) {
    _config = YAML::LoadFile(_filePath.string());

    // Simulation Parameterss
    _gridLength = getGridLength();
    _gridStep = 2. * M_PI / (_gridLength);
    _lambda = 1. / ((double)(_gridLength * _gridLength));
    _dealWN = (unsigned int)(double(_gridLength) * (getDealCoef() / 2.));
    _time = getTime();
    _cfl = getCFL();
    _maxTimeStep = getMaxTimeStep();

    // Equation Coefficients
    _nu = getNu();
    _eta = getEta();

    // Initial Condition Coefficients
    _kineticEnergy = getKineticEnergy();
    _magneticEnergy = getMagneticEnergy();
    _averageWN = getAverageWN();

    // Output Parameters
    _outputStep = getOutputStep();
    _outputStart = getOutputStart();
    _outputStop = getOutputStop();

    // Kernel Run Parameters
    _dimBlockX = getDimBlockX();
    _dimBlockY = getDimBlockY();
    _sharedLength = getSharedLength();
    _linearLength = _gridLength * _gridLength / _sharedLength;

    // Writer Settings
    _saveData = getSaveData();
    _savePNG = getSavePNG();
    _saveVorticity = getSaveVorticity();
    _saveCurrent = getSaveCurrent();
    _saveStream = getSaveStream();
    _savePotential = getSavePotential();

    // Graphics Settings
    _showGraphics = getShowGraphics();
    _texturesCount = getTexturesCount();
    _windowWidth = getWindowWidth();
    _windowHeight = getWindowHeight();
    _colorMap = getColorMap();
}

std::string Configs::ParametersPrint() const {
    std::ostringstream output;

    output << "Simulation parameters:" << std::endl;
    output << "  Grid Lenght = " << std::setw(13) << std::left << _gridLength
           << std::endl;
    output << "  End Time = " << std::setw(12) << std::left << _time
           << std::endl;
    output << std::endl;

    output << "Initial condition:" << std::endl;
    output << "  Ekin = " << std::setw(13) << std::left << _kineticEnergy
           << std::endl;
    output << "  Emag = " << std::setw(13) << std::left << _magneticEnergy
           << std::endl;
    output << std::endl;

    output << "Equation coefficients:" << std::endl;
    output << "  nu = " << std::setw(13) << std::left << _nu << std::endl;
    output << "  eta = " << std::setw(13) << std::left << _eta << std::endl;

    output << std::endl;

    return output.str();
}

void Configs::ParametersSave(const std::filesystem::path& outputDir) const {
    std::ofstream fParams(outputDir / "params.yaml");

    fParams << "gridLength: " << _gridLength << std::endl
            << "time: " << _time << std::endl
            << "Ekin0: " << _kineticEnergy << std::endl
            << "Emag0: " << _magneticEnergy << std::endl
            << "nu: " << _nu << std::endl
            << "eta: " << _eta << std::endl
            << "outStep: " << _outputStep << std::endl
            << "outStart: " << _outputStart << std::endl
            << "outStop: " << _outputStop << std::endl;

    fParams.close();
}

unsigned int Configs::getGridLength() const {
    if (_config["GridLength"]) {
        return _config["GridLength"].as<unsigned int>();
    } else {
        return DefaultConfigs::defaultGridLength;
    }
}

double Configs::getTime() const {
    if (_config["Time"]) {
        return _config["Time"].as<double>();
    } else {
        return DefaultConfigs::defaultTime;
    }
}

double Configs::getDealCoef() const {
    if (_config["DealiasingCoef"]) {
        return _config["DealiasingCoef"].as<double>();
    } else {
        return DefaultConfigs::defaultDealCoef;
    }
}

double Configs::getMaxTimeStep() const {
    if (_config["MaxTimeStep"]) {
        return _config["MaxTimeStep"].as<double>();
    } else {
        return DefaultConfigs::defaultMaxTimeStep;
    }
}

double Configs::getCFL() const {
    if (_config["CFL"]) {
        return _config["CFL"].as<double>();
    } else {
        return DefaultConfigs::defaultCFL;
    }
}

double Configs::getNu() {
    if (_config["nu"]) {
        return _config["nu"].as<double>();
    } else {
        return DefaultConfigs::defaultNu;
    }
}

double Configs::getEta() {
    if (_config["eta"]) {
        return _config["eta"].as<double>();
    } else {
        return DefaultConfigs::defaultEta;
    }
}

double Configs::getKineticEnergy() {
    if (_config["KineticEnergy"]) {
        return _config["KineticEnergy"].as<double>();
    } else {
        return DefaultConfigs::defaultKineticEnergy;
    }
}

double Configs::getMagneticEnergy() {
    if (_config["MagneticEnergy"]) {
        return _config["MagneticEnergy"].as<double>();
    } else {
        return DefaultConfigs::defaultMagneticEnergy;
    }
}

unsigned int Configs::getAverageWN() {
    if (_config["AverageWN"]) {
        return _config["AverageWN"].as<unsigned int>();
    } else {
        return DefaultConfigs::defaultAverageWN;
    }
}

double Configs::getOutputStep() {
    if (_config["OutputStep"]) {
        return _config["OutputStep"].as<double>();
    } else {
        return DefaultConfigs::defaultOutputStep;
    }
}

double Configs::getOutputStart() {
    if (_config["OutputStart"]) {
        return _config["OutputStart"].as<double>();
    } else {
        return DefaultConfigs::defaultOutputStart;
    }
}

double Configs::getOutputStop() {
    if (_config["OutputStop"]) {
        return _config["OutputStop"].as<double>();
    } else {
        return getOutputStep() * DefaultConfigs::defaultMaxOutputs;
    }
}

unsigned int Configs::getDimBlockX() {
    if (_config["DimBlockX"]) {
        return _config["DimBlockX"].as<unsigned int>();
    } else {
        return DefaultConfigs::defaultDimBlockX;
    }
}

unsigned int Configs::getDimBlockY() {
    if (_config["DimBlockX"]) {
        return _config["DimBlockX"].as<unsigned int>();
    } else {
        return DefaultConfigs::defaultDimBlockX;
    }
}

unsigned int Configs::getSharedLength() {
    if (_config["SharedLength"]) {
        return _config["SharedLength"].as<unsigned int>();
    } else {
        return DefaultConfigs::defaultSharedLength;
    }
}

bool Configs::getSaveData() {
    if (_config["SaveData"]) {
        return _config["SaveData"].as<bool>();
    } else {
        return DefaultConfigs::defaultSaveData;
    }
}

bool Configs::getSavePNG() {
    if (_config["SavePNG"]) {
        return _config["SavePNG"].as<bool>();
    } else {
        return DefaultConfigs::defaultSavePNG;
    }
}

bool Configs::getSaveVorticity() {
    if (_config["SaveVorticity"]) {
        return _config["SaveVorticity"].as<bool>();
    } else {
        return DefaultConfigs::defaultSaveVorticity;
    }
}

bool Configs::getSaveCurrent() {
    if (_config["SaveCurrent"]) {
        return _config["SaveCurrent"].as<bool>();
    } else {
        return DefaultConfigs::defaultSaveCurrent;
    }
}

bool Configs::getSaveStream() {
    if (_config["SaveStream"]) {
        return _config["SaveStream"].as<bool>();
    } else {
        return DefaultConfigs::defaultSaveStream;
    }
}

bool Configs::getSavePotential() {
    if (_config["SavePotential"]) {
        return _config["SavePotential"].as<bool>();
    } else {
        return DefaultConfigs::defaultSavePotential;
    }
}

bool Configs::getShowGraphics() {
    if (_config["ShowGraphics"]) {
        return _config["ShowGraphics"].as<bool>();
    } else {
        return DefaultConfigs::defaultShowGraphics;
    }
}

unsigned int Configs::getTexturesCount() {
    if (_config["TexturesCount"]) {
        return _config["TexturesCount"].as<unsigned int>();
    } else {
        return DefaultConfigs::defaultTexturesCount;
    }
}

unsigned int Configs::getWindowWidth() {
    if (_config["WindowWidth"]) {
        return _config["WindowWidth"].as<unsigned int>();
    } else {
        return DefaultConfigs::defaultWindowWidth;
    }
}

unsigned int Configs::getWindowHeight() {
    if (_config["WindowHeight"]) {
        return _config["WindowHeight"].as<unsigned int>();
    } else {
        return DefaultConfigs::defaultWindowHeight;
    }
}
std::string Configs::getColorMap() {
    if (_config["ColorMap"]) {
        return _config["ColorMap"].as<std::string>();
    } else {
        return DefaultConfigs::defaultColorMap;
    }
}
}  // namespace mhd