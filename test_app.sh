#!/bin/bash
# test_app.sh - Comprehensive tests for Unit Converter CLI App

set -e

APP=./unit_converter

fail() {
  echo "Test failed: $1"
  exit 1
}

# Build the app first
make build

# Length Conversions
result=$(echo "cm-to-inch 10" | $APP)
[[ "$result" == *"10 cm = 3.93701 inches"* ]] || fail "cm-to-inch 10"

result=$(echo "inch-to-cm 5" | $APP)
[[ "$result" == *"5 inches = 12.7 cm"* ]] || fail "inch-to-cm 5"

# Temperature Conversions
result=$(echo "celsius-to-fahrenheit 0" | $APP)
[[ "$result" == *"0 C = 32 F"* ]] || fail "celsius-to-fahrenheit 0"

result=$(echo "celsius-to-fahrenheit 100" | $APP)
[[ "$result" == *"100 C = 212 F"* ]] || fail "celsius-to-fahrenheit 100"

result=$(echo "fahrenheit-to-celsius 32" | $APP)
[[ "$result" == *"32 F = 0 C"* ]] || fail "fahrenheit-to-celsius 32"

result=$(echo "fahrenheit-to-celsius 212" | $APP)
[[ "$result" == *"212 F = 100 C"* ]] || fail "fahrenheit-to-celsius 212"

# Energy Conversions (particle physics)
result=$(echo "nat-energy-to-si 1" | $APP)
[[ "$result" == *"1 MeV = 1.6022e-13 J"* ]] || fail "nat-energy-to-si 1"

result=$(echo "nat-energy-to-si 100" | $APP)
[[ "$result" == *"100 MeV = 1.6022e-11 J"* ]] || fail "nat-energy-to-si 100"

result=$(echo "si-energy-to-nat 1.602176634e-13" | $APP)
[[ "$result" == *"1.60218e-13 J = 1 MeV"* ]] || fail "si-energy-to-nat"

# Mass Conversions (particle physics)
result=$(echo "nat-mass-to-si 1" | $APP)
[[ "$result" == *"1 MeV/c² = 1.7827e-30 kg"* ]] || fail "nat-mass-to-si 1"

result=$(echo "nat-mass-to-si 1000" | $APP)
[[ "$result" == *"1000 MeV/c² = 1.7827e-27 kg"* ]] || fail "nat-mass-to-si 1000"

result=$(echo "si-mass-to-nat 1.78266192e-30" | $APP)
[[ "$result" == *"1.78266e-30 kg = 1 MeV/c²"* ]] || fail "si-mass-to-nat"

# Length Conversions (particle physics)
result=$(echo "nat-length-to-si 1" | $APP)
[[ "$result" == *"1 fm = 1e-15 m"* ]] || fail "nat-length-to-si 1"

result=$(echo "nat-length-to-si 0.5" | $APP)
[[ "$result" == *"0.5 fm = 5e-16 m"* ]] || fail "nat-length-to-si 0.5"

result=$(echo "si-length-to-nat 1e-15" | $APP)
[[ "$result" == *"1e-15 m = 1 fm"* ]] || fail "si-length-to-nat"

# Help and error handling
result=$(echo "help" | $APP)
[[ "$result" == *"Commands:"* ]] || fail "help command"

result=$(echo "foo 1" | $APP)
[[ "$result" == *"Unknown or incomplete command"* ]] || fail "unknown command"

# Test exit commands
result=$(echo -e "cm-to-inch 10\nexit" | $APP)
[[ "$result" == *"3.93701 inches"* ]] || fail "exit command"

echo "All tests passed!"
