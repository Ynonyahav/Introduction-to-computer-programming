import json
import sys
import os


def get_usage_as_script_message():
    return "Usage: python3 enigma.py -c <config_file> -i <input_file> -o <output_file>"


def get_script_error_message():
    return "The enigma script has encountered an error"


class JSONFileError(BaseException):
    pass


class InvalidJSONConfigError(BaseException):
    pass


class Wheel:
    def __init__(self, position):
        self.position = position
        self._INITIAL_POSITION = position

    def update_position(self, encrypted_count):
        raise NotImplementedError("Update position method is not implemented for this Wheel")

    def reset_position(self):
        self.position = self._INITIAL_POSITION


class W1(Wheel):
    def __init__(self, position):
        super().__init__(position)
        self._W1_UPDATE_RANGE = range(1, 9)

    def update_position(self, encrypted_count=None):
        self.position += 1
        if self.position not in self._W1_UPDATE_RANGE:
            self.position = 1


class W2(Wheel):
    def __init__(self, position):
        super().__init__(position)
        self._W2_ENCRYPTED_MODULO = 2
        self._W2_MULTIPLY = 2

    def update_position(self, encrypted_count):
        if encrypted_count % self._W2_ENCRYPTED_MODULO == 0:
            self.position *= self._W2_MULTIPLY
        else:
            self.position -= 1


class W3(Wheel):
    def __init__(self, position):
        super().__init__(position)
        self._W3_ENCRYPTED_MODULO = {'A': 10, 'B': 3}
        self._W3_UPDATE_STATES = {'A': 10, 'B': 5, 'DEFAULT': 0}

    def update_position(self, encrypted_count):
        if encrypted_count % self._W3_ENCRYPTED_MODULO['A'] == 0:
            self.position = self._W3_UPDATE_STATES['A']
        elif encrypted_count % self._W3_ENCRYPTED_MODULO['B'] == 0:
            self.position = self._W3_UPDATE_STATES['B']
        else:
            self.position = self._W3_UPDATE_STATES['DEFAULT']


def create_type_wheel_list_3Wheels(wheels):
    return [W1(wheels[0]), W2(wheels[1]), W3(wheels[2])]


class Encryptor3Wheel:
    def __init__(self, hash_map, wheels, reflector_map, encryption_range):
        self.hash_map = hash_map
        self.wheels = wheels
        self.reflector_map = reflector_map
        self.encrypted_count = 0
        self._ENCRYPTION_RANGE = encryption_range

    def get_encryptor_unique_value(self):
        _W1, _W2, _W3 = self.wheels
        _W1_MULTIPLY = 2
        return (_W1_MULTIPLY * _W1.position - _W2.position + _W3.position) % len(self._ENCRYPTION_RANGE)

    def encrypt_single_char(self, c):
        if ord(c) in self._ENCRYPTION_RANGE:
            _UNIQUE_VALUE = self.get_encryptor_unique_value()
            self.encrypted_count += 1
            i = self.hash_map[c]
            if _UNIQUE_VALUE == 0:
                i += 1
            else:
                i += _UNIQUE_VALUE
            i %= len(self._ENCRYPTION_RANGE)
            c1 = next((k for k, v in self.hash_map.items() if v == i), None)
            c2 = self.reflector_map[c1]
            i = self.hash_map[c2]
            if _UNIQUE_VALUE == 0:
                i -= 1
            else:
                i -= _UNIQUE_VALUE
            i %= len(self._ENCRYPTION_RANGE)
            c3 = next((k for k, v in self.hash_map.items() if v == i), None)
            return c3
        else:
            return c

    def reset_encrypted_count(self):
        self.encrypted_count = 0


class Enigma:
    def __init__(self, hash_map, wheels, reflector_map):
        self.wheels = create_type_wheel_list_3Wheels(wheels)
        self._ENCRYPTION_RANGE = range(ord('a'), ord('z') + 1)
        self.encryptor = Encryptor3Wheel(hash_map, self.wheels, reflector_map, self._ENCRYPTION_RANGE)

    def update_wheels(self, encrypted_count):
        for wheel in self.wheels:
            wheel.update_position(encrypted_count)

    def reset_wheels(self):
        for wheel in self.wheels:
            wheel.reset_position()

    def encrypt(self, message):
        result = ''
        for char in message:
            result += self.encryptor.encrypt_single_char(char)
            self.update_wheels(self.encryptor.encrypted_count)
        self.reset_wheels()
        self.encryptor.reset_encrypted_count()
        return result


def encrypt_messages(enigma, messages, output_path=None):
    result = ''.join(map(enigma.encrypt, messages))
    if output_path is not None:
        with open(output_path, 'w') as output_file:
            output_file.write(result)
    else:
        print(result)


def validate_hash_map(hash_map, encryption_range):
    return (isinstance(hash_map, dict)
            and all(chr(letter) in hash_map.keys() for letter in encryption_range)
            and all(value in hash_map.values() for value in range(len(encryption_range))))


def validate_wheels(wheels, number_of_wheels):
    return (isinstance(wheels, list)
            and len(wheels) == number_of_wheels
            and all(isinstance(wheel, int) for wheel in wheels))


def validate_reflector_map(reflector_map, encryption_range):
    return (isinstance(reflector_map, dict)
            and all(chr(letter) in reflector_map.keys() for letter in encryption_range)
            and all(reflector_map[reflector_map[k]] == k for k in reflector_map))


def validate_JSON_config_file(config_data):
    _NUMBER_OF_WHEELS = 3
    _ENCRYPTION_RANGE = range(ord('a'), ord('z') + 1)
    if (not validate_hash_map(config_data['hash_map'], _ENCRYPTION_RANGE)
            or not validate_wheels(config_data['wheels'], _NUMBER_OF_WHEELS)
            or not validate_reflector_map(config_data['reflector_map'], _ENCRYPTION_RANGE)):
        raise InvalidJSONConfigError


def load_enigma_from_path(path):
    try:
        with open(path, 'r') as config_file:
            data = json.load(config_file)
        validate_JSON_config_file(data)
        return Enigma(data['hash_map'], data['wheels'], data['reflector_map'])
    except:
        raise JSONFileError


def load_messages_from_path(path):
    with open(path, 'r') as messages_file:
        data = messages_file.readlines()
    return data


def main():
    # Input arguments count check. Should be 5 or 7
    _ARGS_COUNT = (5, 7)
    if len(sys.argv) not in _ARGS_COUNT:
        print(get_usage_as_script_message(), file=sys.stderr)
        sys.exit(1)

    # Flags and Arguments check and parsing
    _FLAGS = {'flag_config': '-c', 'flag_input': '-i', 'flag_output': '-o'}
    args_map = {sys.argv[i]: sys.argv[i + 1] for i in range(1, len(sys.argv), 2)}
    for flag in args_map.keys():
        if flag not in _FLAGS.values() or (flag != '-o' and not os.path.exists(args_map[flag])):
            print(get_usage_as_script_message(), file=sys.stderr)
            sys.exit(1)

    # Execute program procedure
    try:
        enigma = load_enigma_from_path(args_map[_FLAGS['flag_config']])
        messages = load_messages_from_path(args_map[_FLAGS['flag_input']])
        output_path = None
        if _FLAGS['flag_output'] in args_map:
            output_path = args_map[_FLAGS['flag_output']]
        encrypt_messages(enigma, messages, output_path)
    except:
        print(get_script_error_message(), file=sys.stderr)
        sys.exit(1)

    sys.exit(0)


if __name__ == '__main__':
    main()

