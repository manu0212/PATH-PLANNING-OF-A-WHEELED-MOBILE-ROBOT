#include <AccelStepper.h>

// Define stepper motor connections and steps per revolution
#define STEPS_PER_REVOL 200
#define X_STEP_PIN 2
#define X_DIR_PIN 5

// Define Function to calculate steps based on distance and wheel diameter
long calculateSteps(float distance, float wheelDiameter) {
  // Convert distance to millimeters (adjust if needed)
  distance = 100.0; // Millimeters per meter
  wheelDiameter = 31.8471338;
  
  // Calculate circumference
  float circumference = PI * wheelDiameter;
  
  // Calculate steps per millimeter
  float stepsPerMillimeter = STEPS_PER_REVOL / circumference;
  
  // Calculate total steps
  long steps = stepsPerMillimeter * distance;
  
  return steps;
}

// Create an AccelStepper object for the X motor
AccelStepper stepperX(AccelStepper::DRIVER, X_STEP_PIN, X_DIR_PIN);

void setup() {
  // Set maximum speed and acceleration for X motor
  stepperX.setMaxSpeed(100);
  stepperX.setAcceleration(500);

  // Open serial communication
  Serial.begin(9600); // Adjust baud rate if needed
  while (!Serial) { // Wait for serial connection to be established
    ;
  }
  Serial.println("Starting motor control...");
}

void loop() {
  // Define target distance in mm (replace with your input method)
  float targetDistance = 100.0; // Example value

  // Calculate required steps
  long steps = calculateSteps(targetDistance, 100); // Replace 100 with your actual wheel diameter

  // Print calculated steps to serial monitor
  Serial.print("Calculated steps: ");
  Serial.println(steps);

  // Move the motor to the desired position
  stepperX.moveTo(steps);

  // Wait for movement to finish
  while (stepperX.isRunning()) {
    stepperX.run();
  }

  // Optional: wait some time before repeating
  delay(1000);
}
