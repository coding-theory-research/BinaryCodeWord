//
// Created by Nathan Russell on 2/3/26.
//

#ifndef BINARYCODEWORD_ERRORMESSAGES_HPP
#define BINARYCODEWORD_ERRORMESSAGES_HPP


namespace bcw::error {

    inline constexpr const char* length_nonpositive =
        "BinaryCodeWord: codeword length must be an integer greater than zero";

    inline constexpr const char* position_oob =
        "BinaryCodeWord: bit position out of range";

    inline constexpr const char* length_mismatch_plus =
        "BinaryCodeWord::operator+: codeword lengths must match";

    inline constexpr const char* length_mismatch_pluseq =
        "BinaryCodeWord::operator+=: codeword lengths must match";

}
#endif //BINARYCODEWORD_ERRORMESSAGES_HPP