# ATTENTION: This should work for arduino-cli program
# only if you have espress 32 Boards Packages
# https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html

ARDUINO_JSON = arduino.json
# Check if arduino.json exists
ifeq ($(shell test -e $(ARDUINO_JSON) && echo -n yes),yes)
  # If arduino.json exists, proceed with reading it
  SKETCH_NAME = $(shell jq -r '.sketch' $(ARDUINO_JSON))
	BOARD = $(shell jq -r '.board' $(ARDUINO_JSON))
	PORT = $(shell jq -r '.port' $(ARDUINO_JSON))
else
  $(error arduino.json not found. Please ensure the file exists.)
endif

# Define commands to compile and upload
COMPILE = arduino-cli compile --fqbn $(BOARD) $(SKETCH)
UPLOAD = arduino-cli upload -p $(PORT) --fqbn $(BOARD) $(SKETCH)

# Default target (will run both compile and upload)
all: compile upload

# Targets
compile:
	@echo "Compiling $(SKETCH)..."
	$(COMPILE)

upload:
	@echo "Uploading $(SKETCH) to ESP32..."
	$(UPLOAD)

clean:
	@echo "Cleaning compiled files..."
	# rm -rf $(SKETCH).elf $(SKETCH).bin $(SKETCH).hex
