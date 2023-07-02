# Badgerloop Autocoding

## What is Autocoding
Autocoding is the act of a program that will write code for you based on a set of inputs.

In Badgerloop we implement this using Python and a json file for all of our sensors.

## Why do we do it
A lot of our data gathering and telemetry is based off the total number and variety of sensors we put on the car. It is simply a hassle to change all the different parts of our codebase if we want to add, remove, or change a sensor. Using one single source of truth, our format.json file, we can automatically change the relevant code.

## How to Autocode

### 1. Creating a template

First step is to create the file that will be populated with the format.json file. Usually setting up init functions or imports is done in the template. Create a placeholder comment where you would like the autogenerated code to be placed.

### 2. Create the generator

In `generators.py` create a new function that takes in one parameter. This parameter is the json file that will be used to populate the template. An example is provided in this file. Use the `util.py` library to ease this process. This generator will take the JSON input and output a string of C/C++ code.

### 3. Call the generator

In `autocode.py` create a new instance of the `AutoGeneratedFile` class. This class will take in the template file and output file. Then call the `autocode` function that takes in the placeholder string to search for and the generator to use.

`autocode.py` is called automatically on build so there is no need to manually run the script. However `python3 autocoding/autocode.py` is helpful for debugging.