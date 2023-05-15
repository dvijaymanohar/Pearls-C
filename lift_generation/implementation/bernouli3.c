#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Constants
#define PI 3.14159265359

// Airfoil parameters
const double chord_length = 1.0;    // meters
const double camber = 0.02;         // meters
const double thickness = 0.01;      // meters
const double angle_of_attack = 5.0; // degrees

// Atmospheric parameters
const double sea_level_pressure = 101325.0;    // Pa
const double sea_level_temperature = 288.15;   // K
const double sea_level_density = 1.225;        // kg/m^3
const double temperature_lapse_rate = -0.0065; // K/m
const double gravity = 9.81;                   // m/s^2
// const double gamma = 1.4;                      // ratio of specific heats
const double R = 287.058; // J/(kg*K)

// Pitot tube parameters
const double pitot_tube_diameter = 0.005;         // meters
const double pitot_tube_correction_factor = 0.97; // dimensionless

// Measurement uncertainties
const double chord_uncertainty = 0.001;                       // meters
const double camber_uncertainty = 0.0005;                     // meters
const double thickness_uncertainty = 0.0005;                  // meters
const double angle_of_attack_uncertainty = 0.1;               // degrees
const double pitot_tube_correction_factor_uncertainty = 0.01; // dimensionless

double get_density(double altitude) {
  // Calculate the air density based on the altitude using the ISA model
  double temperature =
      sea_level_temperature + temperature_lapse_rate * altitude;
  double pressure =
      sea_level_pressure * pow(temperature / sea_level_temperature,
                               -gravity / (R * temperature_lapse_rate));
  double density = pressure / (R * temperature);
  return density;
}

double get_pressure(double altitude) {
  // Calculate the air pressure based on the altitude using the ISA model
  double temperature =
      sea_level_temperature + temperature_lapse_rate * altitude;
  double pressure =
      sea_level_pressure * pow(temperature / sea_level_temperature,
                               -gravity / (R * temperature_lapse_rate));
  return pressure;
}

double get_speed_of_sound(double altitude) {
  const double gamma = 1.4; // ratio of specific heats

  // Calculate the speed of sound based on the altitude using the ISA model
  double temperature =
      sea_level_temperature + temperature_lapse_rate * altitude;
  double speed_of_sound = sqrt(gamma * R * temperature);
  return speed_of_sound;
}

double get_mach_number(double velocity, double altitude) {
  // Calculate the Mach number based on the velocity and altitude
  double speed_of_sound = get_speed_of_sound(altitude);
  double mach_number = velocity / speed_of_sound;
  return mach_number;
}

double get_coefficient_of_pressure(double mach_number) {
  const double gamma = 1.4; // ratio of specific heats

  // Calculate the coefficient of pressure based on the Mach number using the
  // Prandtl-Glauert rule
  double mach_correction_factor =
      sqrt((gamma + 1) / 2) /
      (1 + 0.5 * (gamma - 1) * mach_number * mach_number);
  double coefficient_of_pressure =
      1 / (mach_correction_factor * mach_correction_factor);
  return coefficient_of_pressure;
}

double get_dynamic_pressure(double velocity, double altitude) {
  // Calculate the dynamic pressure based on the velocity and altitude
  double density = get_density(altitude);
  double dynamic_pressure = 0.5 * density * velocity * velocity;
  return dynamic_pressure;
}

// Function to generate normally distributed random numbers
double randn(double mean, double stddev) {
  double u1, u2, z;
  u1 = rand() * (1.0 / RAND_MAX);
  u2 = rand() * (1.0 / RAND_MAX);
  z = sqrt(-2.0 * log(u1)) * cos(2.0 * PI * u2);
  return mean + stddev * z;
}

// Function to calculate lift coefficient
double lift_coefficient(double air_density, double air_velocity,
                        double air_pressure, double pitot_tube,
                        double temperature, double humidity, double elevation,
                        double chord_length, double angle_of_attack) {
  // Calculate dynamic pressure from Pitot tube reading
  double dynamic_pressure = 0.5 * air_density * pow(air_velocity, 2);
  double pitot_correction = 1 + 0.2 * pow(pitot_tube, 2) / pow(air_velocity, 2);

  // Calculate environmental parameters with uncertainty
  double pressure_at_sea_level = randn(101325.0, 1000.0);
  double temperature_at_sea_level = randn(288.15, 1.0);
  double lapse_rate = 0.0065;
  double relative_humidity = randn(humidity, 5.0);
  double saturation_pressure =
      611.21 * exp(17.502 * temperature / (240.97 + temperature));
  double vapor_pressure = saturation_pressure * relative_humidity;
  double dry_air_density =
      air_density * (pressure_at_sea_level - 0.3783 * elevation) /
      (pressure_at_sea_level * (temperature / temperature_at_sea_level) *
       pow(pitot_correction, 2));
  double water_vapor_density =
      vapor_pressure * 0.622 /
      (pressure_at_sea_level * (temperature / temperature_at_sea_level) *
       pow(pitot_correction, 2));
  double air_density_corrected = dry_air_density + water_vapor_density;

  // Calculate lift coefficient using Bernoulli equation with uncertainty
  double lift = 2 * PI * chord_length * pow(dynamic_pressure, 1.5) *
                air_density_corrected * sin(angle_of_attack) /
                sqrt(pow(air_velocity, 2) * pow(chord_length, 2));
  return lift;
}

// Function to generate random number within a range using a non-uniform
// empirical distribution
double generate_random_number(double min, double max, double mode) {
  double range = max - min;
  double x = (double)rand() / RAND_MAX;
  double y = (double)rand() / RAND_MAX;
  double mu = mode - min;
  double sigma = (mode - min) * (max - mode) / pow(range, 2);
  double u = sqrt(-2 * log(x)) * cos(2 * PI * y);
  double v = mu + sigma * u;

  if (v < min) {
    v = min;
  } else if (v > max) {
    v = max;
  }

  return v;
}

double rand_range(double min, double max) {
  double range = max - min;
  double random_num = ((double)rand()) / RAND_MAX;
  return (random_num * range) + min;
}

int main() {
  // Set input parameters with uncertainties

#if 0
  double air_density =
      1.225; // kg/m^3, +/- 0.02 kg/m^3 (source:
             // https://www.engineeringtoolbox.com/standard-atmosphere-d_604.html)
#endif

  double air_density = generate_random_number(
      1.2, 1.25,
      1.225); // kg/m^3, +/- 0.02 kg/m^3 (source:
              // https://www.engineeringtoolbox.com/standard-atmosphere-d_604.html)

  double air_velocity = generate_random_number(
      9.5, 10.5,
      10.0); // m/s, +/- 0.1 m/s (source:
             // https://www.engineeringtoolbox.com/air-speed-velocity-d_1783.html)

  double air_pressure = generate_random_number(
      100325, 103325,
      101325.0); // Pa, +/- 1000 Pa (source:
                 // https://www.engineeringtoolbox.com/standard-atmosphere-d_604.html)

  double pitot_tube = generate_random_number(
      4.95, 5.05,
      5.0); // m/s, +/- 0.05 m/s (source:
            // https://www.engineeringtoolbox.com/pitot-tubes-d_641.html)

  double temperature = generate_random_number(19, 21, 20);
  // deg C, +/- 1 deg C (source:
  // https://www.engineeringtoolbox.com/air-properties-d_156.html)

  double humidity = generate_random_number(48.5, 52.5, 50);
  // %, +/- 5% (source:
  // https://www.engineeringtoolbox.com/humidity-ratio-d_585.html)

  double elevation = generate_random_number(990.0, 1010.0, 1000.0);
  // m, +/- 10 m (source:
  // https://www.engineeringtoolbox.com/standard-atmosphere-d_604.html)

  double chord_length = 2.0;                 // m
  double angle_of_attack = 5.0 * PI / 180.0; // radians

  // Calculate measurement uncertainties for each parameter
  double air_density_uncertainty = 0.02 / air_density;  // relative uncertainty
  double air_velocity_uncertainty = 0.1 / air_velocity; // relative uncertainty
  double air_pressure_uncertainty =
      1000.0 / air_pressure;                          // relative uncertainty
  double pitot_tube_uncertainty = 0.05 / pitot_tube;  // relative uncertainty
  double temperature_uncertainty = 1.0 / temperature; // relative uncertainty
  double humidity_uncertainty = 0.05;                 // absolute uncertainty
  double elevation_uncertainty = 10.0 / elevation;    // relative uncertainty
  double chord_length_uncertainty = 0.0;    // no uncertainty specified
  double angle_of_attack_uncertainty = 0.0; // no uncertainty specified

  // Calculate lift coefficient with uncertainties
  double lift = lift_coefficient(air_density, air_velocity, air_pressure,
                                 pitot_tube, temperature, humidity, elevation,
                                 chord_length, angle_of_attack);
  double lift_uncertainty =
      sqrt(pow(air_density_uncertainty, 2) + pow(air_velocity_uncertainty, 2) +
           pow(air_pressure_uncertainty, 2) + pow(pitot_tube_uncertainty, 2) +
           pow(temperature_uncertainty, 2) + pow(humidity_uncertainty, 2) +
           pow(elevation_uncertainty, 2));

  // Output lift coefficient and uncertainty
  printf("Lift coefficient: %f +/- %f\n", lift, lift_uncertainty);

  return 0;
}