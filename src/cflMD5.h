#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>

// Rotate left operation. Shifts bits to the left and wraps the overflow bits around to the right side.
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32 - (n))))

// Constants for MD5 rounds.
const uint32_t k1 = 0x5A827999;
const uint32_t k2 = 0x6ED9EBA1;
const uint32_t k3 = 0x8F1BBCDC;
const uint32_t k4 = 0xCA62C1D6;

// Initial hash values for MD5.
const uint32_t h0 = 0x67452301;
const uint32_t h1 = 0xEFCDAB89;
const uint32_t h2 = 0x98BADCFE;
const uint32_t h3 = 0x10325476;

// Padding bits for input message.
const uint8_t kPaddingBits[64] = { 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
								  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
								  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
								  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

std::string md5(const std::string& message)
{
	uint32_t message_length = message.length();

	// Initialize the hash values.
	uint32_t a = h0;
	uint32_t b = h1;
	uint32_t c = h2;
	uint32_t d = h3;

	// Pad the message.
	uint64_t bit_length = (uint64_t)message_length * 8;
	uint32_t padding_length = message_length % 64 < 56 ? 56 - message_length % 64 : 120 - message_length % 64;
	std::string padded_message(message);
	padded_message += std::string((char*)kPaddingBits, padding_length);
	padded_message += std::string((char*)&bit_length, 8);

	// Process the padded message in 64-byte chunks.
	for (uint32_t i = 0; i < padded_message.length(); i += 64)
	{
		// Get the 16 32-bit words from the message block.
		uint32_t words[16];
		for (uint32_t j = 0; j < 16; j++)
		{
			uint32_t word = 0;
			for (uint32_t k = 0; k < 4; k++)
			{
				word |= ((uint32_t)padded_message[i + j * 4 + k] << (k * 8));
			}
			words[j] = word;
		}

		// Save the current hash values.
		uint32_t aa = a;
		uint32_t bb = b;
		uint32_t cc = c;
		uint32_t dd = d;
		// Round 1.
		for (uint32_t j = 0; j < 16; j++)
		{
			uint32_t f = (b & c) | ((~b) & d);
			uint32_t g = j;
			uint32_t temp = d;
			d = c;
			c = b;
			b = b + ROTATE_LEFT((a + f + words[g] + k1), 7);
			a = temp;
		}
		// Round 2.
		for (uint32_t j = 0; j < 16; j++)
		{
			uint32_t f = (d & b) | ((~d) & c);
			uint32_t g = (5 * j + 1) % 16;
			uint32_t temp = d;
			d = c;
			c = b;
			b = b + ROTATE_LEFT((a + f + words[g] + k2), 12);
			a = temp;
		}

		// Round 3.
		for (uint32_t j = 0; j < 16; j++)
		{
			uint32_t f = b ^ c ^ d;
			uint32_t g = (3 * j + 5) % 16;
			uint32_t temp = d;
			d = c;
			c = b;
			b = b + ROTATE_LEFT((a + f + words[g] + k3), 17);
			a = temp;
		}

		// Round 4.
		for (uint32_t j = 0; j < 16; j++)
		{
			uint32_t f = c ^ (b | (~d));
			uint32_t g = (7 * j) % 16;
			uint32_t temp = d;
			d = c;
			c = b;
			b = b + ROTATE_LEFT((a + f + words[g] + k4), 22);
			a = temp;
		}

		// Add the compressed chunk to the current hash values.
		a += aa;
		b += bb;
		c += cc;
		d += dd;
	}

	// Construct the final hash value.
	uint8_t hash[16];
	memcpy(hash, &a, 4);
	memcpy(hash + 4, &b, 4);
	memcpy(hash + 8, &c, 4);
	memcpy(hash + 12, &d, 4);

	// Convert the hash value to a string of hexadecimal digits.
	std::string hash_string;
	for (uint32_t i = 0; i < 16; i++)
	{
		hash_string += std::to_string(hash[i] >> 4 & 0xf);
		hash_string += std::to_string(hash[i] & 0xf);
	}

	return hash_string;
}