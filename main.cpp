#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <map>
#include <functional>

// Global quiet flag (suppress UI elements like prompts and welcome message)
bool g_quiet = false;

// Conversion Constants (CODATA 2018 values and SI definitions)
const double CM_TO_INCH = 1.0 / 2.54;
const double INCH_TO_CM = 2.54;
const double CELSIUS_TO_FAHRENHEIT_FACTOR = 9.0 / 5.0;
const double CELSIUS_TO_FAHRENHEIT_OFFSET = 32.0;
const double MEV_TO_JOULES = 1.602176634e-13;
const double MASS_MEV_TO_KG = 1.78266192e-30;
const double FM_TO_M = 1.0e-15;
const int OUTPUT_PRECISION = 5;

void show_help()
{
    std::cout << "Commands:\n";
    std::cout << "  cm-to-inch [cm]              - Convert centimeters to inches\n";
    std::cout << "  inch-to-cm [inch]            - Convert inches to centimeters\n";
    std::cout << "  celsius-to-fahrenheit [temp] - Convert Celsius to Fahrenheit\n";
    std::cout << "  fahrenheit-to-celsius [temp] - Convert Fahrenheit to Celsius\n";
    std::cout << "  nat-energy-to-si [MeV]      - Convert natural energy units to Joules\n";
    std::cout << "  si-energy-to-nat [J]        - Convert Joules to natural energy units\n";
    std::cout << "  nat-mass-to-si [MeV/c²]     - Convert natural mass units to kilograms\n";
    std::cout << "  si-mass-to-nat [kg]         - Convert kilograms to natural mass units\n";
    std::cout << "  nat-length-to-si [fm]       - Convert natural length units to meters\n";
    std::cout << "  si-length-to-nat [m]        - Convert meters to natural length units\n";
    std::cout << "  exit, quit, q                - Quit the app\n";
}

// Converts centimeters to inches
// Formula: inches = cm / 2.54
void convert_cm_to_inch(std::istringstream &iss)
{
    double cm;
    if (iss >> cm)
    {
        double inch = cm * CM_TO_INCH;
        std::cout << cm << " cm = " << std::fixed << std::setprecision(OUTPUT_PRECISION)
                  << inch << " inches\n";
    }
    else
    {
        std::cout << "Usage: cm-to-inch [cm]\n";
    }
}

// Converts inches to centimeters
// Formula: cm = inches * 2.54
void convert_inch_to_cm(std::istringstream &iss)
{
    double inch;
    if (iss >> inch)
    {
        double cm = inch * INCH_TO_CM;
        std::cout << inch << " inches = " << std::setprecision(OUTPUT_PRECISION)
                  << cm << " cm\n";
    }
    else
    {
        std::cout << "Usage: inch-to-cm [inch]\n";
    }
}

// Converts Celsius to Fahrenheit
// Formula: F = (C * 9/5) + 32
void convert_celsius_to_fahrenheit(std::istringstream &iss)
{
    double celsius;
    if (iss >> celsius)
    {
        double fahrenheit = (celsius * CELSIUS_TO_FAHRENHEIT_FACTOR) + CELSIUS_TO_FAHRENHEIT_OFFSET;
        std::cout << celsius << " C = " << std::setprecision(OUTPUT_PRECISION)
                  << fahrenheit << " F\n";
    }
    else
    {
        std::cout << "Usage: celsius-to-fahrenheit [temp]\n";
    }
}

// Converts Fahrenheit to Celsius
// Formula: C = (F - 32) * 5/9
void convert_fahrenheit_to_celsius(std::istringstream &iss)
{
    double fahrenheit;
    if (iss >> fahrenheit)
    {
        double celsius = (fahrenheit - CELSIUS_TO_FAHRENHEIT_OFFSET) / CELSIUS_TO_FAHRENHEIT_FACTOR;
        std::cout << fahrenheit << " F = " << std::setprecision(OUTPUT_PRECISION)
                  << celsius << " C\n";
    }
    else
    {
        std::cout << "Usage: fahrenheit-to-celsius [temp]\n";
    }
}

// Converts natural energy units (MeV) to SI units (Joules)
// Formula: J = MeV * 1.602176634e-13 (CODATA 2018)
void convert_natural_energy_to_si(std::istringstream &iss)
{
    double mev;
    if (iss >> mev)
    {
        double joules = mev * MEV_TO_JOULES;
        std::cout << mev << " MeV = " << std::setprecision(OUTPUT_PRECISION)
                  << joules << " J\n";
    }
    else
    {
        std::cout << "Usage: nat-energy-to-si [MeV]\n";
    }
}

// Converts SI energy units (Joules) to natural units (MeV)
// Formula: MeV = J / 1.602176634e-13 (CODATA 2018)
void convert_si_energy_to_natural(std::istringstream &iss)
{
    double joules;
    if (iss >> joules)
    {
        double mev = joules / MEV_TO_JOULES;
        std::cout << joules << " J = " << std::setprecision(OUTPUT_PRECISION)
                  << mev << " MeV\n";
    }
    else
    {
        std::cout << "Usage: si-energy-to-nat [J]\n";
    }
}

// Converts natural mass units (MeV/c²) to SI units (kilograms)
// Formula: kg = MeV/c² * 1.78266192e-30 (CODATA 2018)
void convert_natural_mass_to_si(std::istringstream &iss)
{
    double mev_over_c2;
    if (iss >> mev_over_c2)
    {
        double kg = mev_over_c2 * MASS_MEV_TO_KG;
        std::cout << mev_over_c2 << " MeV/c² = " << std::setprecision(OUTPUT_PRECISION)
                  << kg << " kg\n";
    }
    else
    {
        std::cout << "Usage: nat-mass-to-si [MeV/c²]\n";
    }
}

// Converts SI mass units (kilograms) to natural units (MeV/c²)
// Formula: MeV/c² = kg / 1.78266192e-30 (CODATA 2018)
void convert_si_mass_to_natural(std::istringstream &iss)
{
    double kg;
    if (iss >> kg)
    {
        double mev_over_c2 = kg / MASS_MEV_TO_KG;
        std::cout << kg << " kg = " << std::setprecision(OUTPUT_PRECISION)
                  << mev_over_c2 << " MeV/c²\n";
    }
    else
    {
        std::cout << "Usage: si-mass-to-nat [kg]\n";
    }
}

// Converts natural length units (femtometers) to SI units (meters)
// Formula: m = fm * 1.0e-15
void convert_natural_length_to_si(std::istringstream &iss)
{
    double fm;
    if (iss >> fm)
    {
        double m = fm * FM_TO_M;
        std::cout << fm << " fm = " << std::setprecision(OUTPUT_PRECISION)
                  << m << " m\n";
    }
    else
    {
        std::cout << "Usage: nat-length-to-si [fm]\n";
    }
}

// Converts SI length units (meters) to natural units (femtometers)
// Formula: fm = m / 1.0e-15
void convert_si_length_to_natural(std::istringstream &iss)
{
    double m;
    if (iss >> m)
    {
        double fm = m / FM_TO_M;
        std::cout << m << " m = " << std::setprecision(OUTPUT_PRECISION)
                  << fm << " fm\n";
    }
    else
    {
        std::cout << "Usage: si-length-to-nat [m]\n";
    }
}

// Dispatch command to appropriate handler
bool process_command(const std::string &cmd, std::istringstream &iss)
{
    // Map of command names to conversion functions
    static const std::map<std::string, std::function<void(std::istringstream&)>> commands = {
        {"cm-to-inch", convert_cm_to_inch},
        {"inch-to-cm", convert_inch_to_cm},
        {"celsius-to-fahrenheit", convert_celsius_to_fahrenheit},
        {"fahrenheit-to-celsius", convert_fahrenheit_to_celsius},
        {"nat-energy-to-si", convert_natural_energy_to_si},
        {"si-energy-to-nat", convert_si_energy_to_natural},
        {"nat-mass-to-si", convert_natural_mass_to_si},
        {"si-mass-to-nat", convert_si_mass_to_natural},
        {"nat-length-to-si", convert_natural_length_to_si},
        {"si-length-to-nat", convert_si_length_to_natural}
    };

    if (cmd == "exit" || cmd == "quit" || cmd == "q")
    {
        return false;
    }
    else if (cmd == "help")
    {
        show_help();
    }
    else if (commands.count(cmd))
    {
        commands.at(cmd)(iss);
    }
    else
    {
        std::cout << "Unknown or incomplete command. Use 'help' for instructions.\n";
    }
    return true;
}

int main(int argc, char *argv[])
{
    // Parse command-line arguments
    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if (arg == "-q" || arg == "--quiet")
        {
            g_quiet = true;
        }
    }

    if (!g_quiet)
    {
        std::cout << "Unit Converter CLI App\n";
        std::cout << "Type 'help' for available commands, or 'exit'/'quit'/'q' to quit:\n";
    }

    std::string line;
    while (true)
    {
        if (!g_quiet)
            std::cout << "> ";
        if (!std::getline(std::cin, line))
            break;
        if (line.empty())
            continue;

        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;

        if (!process_command(cmd, iss))
            break;
    }
    return 0;
}
