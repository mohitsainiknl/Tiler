import json


class PresetParser:
    def __init__(self, file_path):
        self.file_path = file_path
        self.presets = {}

    def load_presets(self):
        """
        Load presets from the JSON file.
        """
        try:
            print(f"\nLoading {self.file_path} for parsing...\n")
            with open(self.file_path, 'r') as file:
                self.presets = json.load(file)
        except FileNotFoundError:
            print("File not found.")

    def save_presets(self):
        """
        Save presets to the JSON file.
        """
        with open(self.file_path, 'w') as file:
            json.dump(self.presets, file, indent=4)
            print(f"\nParsed preset written successfully: {self.file_path} for parsing...")

    def preset(self, code):
        """
        Interpret and execute preset codes.
        """
        in_quotes = False
        transformed_code = ""

        # Transform the preset code for interpretation
        for char in code:
            if char == '"':
                in_quotes = not in_quotes
                transformed_code += char
            elif in_quotes and char == '.':
                transformed_code += '@'
            elif char != ' ':
                transformed_code += char

        # Split the code into keys for navigation
        keys = transformed_code.split('.')
        current_preset = self.presets

        for key in keys:
            # Initialize variables for parsing
            in_list = False
            in_list_value = False
            list_key = ""
            list_value = ""
            oper_equal = False
            remove_value = False
            has_value = False
            new_key = ""
            new_value = ""

            # Parse each key segment
            for char in key:
                if char in ['[', ']']:
                    in_list = True
                elif has_value:
                    new_value += char
                elif in_list and char == '"':
                    in_list_value = True
                elif in_list and not in_list_value and char == '=':
                    oper_equal = True
                elif in_list and not in_list_value and char == '-':
                    remove_value = True
                elif not in_list and char == '=':
                    has_value = True
                elif in_list and in_list_value:
                    list_value += char
                elif in_list and not in_list_value:
                    list_key += char
                elif not in_list:
                    new_key += char

            # Ensure existence of keys in the preset structure
            if new_key not in current_preset:
                if in_list and not oper_equal:
                    current_preset[new_key] = []
                else:
                    current_preset[new_key] = {}

            # Navigate to the appropriate level in the preset structure
            if not has_value:
                current_preset = current_preset[new_key]

            # Handle list operations and value assignments
            if new_key and (in_list_value or has_value):
                if remove_value:
                    print(f"operation : Removing {code.replace(' -- ', '')}")
                    current_preset.remove(list_value)
                elif not remove_value and not oper_equal and not has_value:
                    print(f"operation : Adding {code}")
                    if list_value not in current_preset:
                        current_preset.append(list_value.replace("@", "."))
                elif oper_equal:
                    found = False
                    for value in current_preset:
                        if value[list_key] == list_value:
                            current_preset = value
                            found = True
                            break
                    if not found:
                        new_value = {list_key: list_value}
                        current_preset.append(new_value)
                        current_preset = current_preset[-1]
                elif has_value:
                    print(f"operation : Setting {code}")
                    new_value = new_value.strip()
                    if new_value.startswith('"'):
                        current_preset[new_key] = new_value.replace('"', "").replace("@", ".")
                    elif new_value in ["ON", "True", "1"]:
                        current_preset[new_key] =  True
                    elif new_value in ["OFF", "False", "0"]:
                        current_preset[new_key] = False
                    else:
                        current_preset[new_key] = new_value

        # Return the value if requested
        if new_key and not has_value and not in_list:
            return current_preset[new_key]


# # Usage example
# parser = PresetParser('path/to/CMakePresets.json')
# parser.load_presets()
# 
# # Examples of preset usage
# parser.preset('configurePresets[name=="conan-default"].cacheVariables.CMAKE_BUILD_TYPE = "Release"')    # Add variable
# parser.preset('configurePresets[name=="conan-default"].cacheVariables.CMAKE_BUILD_TYPE')    # return "Release"
# parser.preset('configurePresets[name=="conan-default"].name = "tiler-release"')    # rename name
# parser.preset('configurePresets[name=="conan-default"]')    # create new object with name
# parser.preset('include["TilerPresets.json"]')    # add to list
# parser.preset('include[ -- "TilerPresets.json"]')    # remove from list
# 
# # Save the modified presets
# parser.save_presets()
