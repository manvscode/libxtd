/*
 * Copyright (C) 2025 by Joseph A. Marrero. https://joemarrero.com/
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define AES_BLOCK_SIZE 16
#define AES_256_ROUNDS 14
#define AES_EXPANDED_KEY_SIZE 240

/*
 * Forward S-box
 */
static const uint8_t sbox[256] = {
    /* [omitted in this explanation—but implemented in full below] */
    0x63,0x7c,0x77,0x7b,0xf2,0x6b,0x6f,0xc5,0x30,0x01,0x67,0x2b,0xfe,0xd7,0xab,0x76,
    0xca,0x82,0xc9,0x7d,0xfa,0x59,0x47,0xf0,0xad,0xd4,0xa2,0xaf,0x9c,0xa4,0x72,0xc0,
    0xb7,0xfd,0x93,0x26,0x36,0x3f,0xf7,0xcc,0x34,0xa5,0xe5,0xf1,0x71,0xd8,0x31,0x15,
    0x04,0xc7,0x23,0xc3,0x18,0x96,0x05,0x9a,0x07,0x12,0x80,0xe2,0xeb,0x27,0xb2,0x75,
    0x09,0x83,0x2c,0x1a,0x1b,0x6e,0x5a,0xa0,0x52,0x3b,0xd6,0xb3,0x29,0xe3,0x2f,0x84,
    0x53,0xd1,0x00,0xed,0x20,0xfc,0xb1,0x5b,0x6a,0xcb,0xbe,0x39,0x4a,0x4c,0x58,0xcf,
    0xd0,0xef,0xaa,0xfb,0x43,0x4d,0x33,0x85,0x45,0xf9,0x02,0x7f,0x50,0x3c,0x9f,0xa8,
    0x51,0xa3,0x40,0x8f,0x92,0x9d,0x38,0xf5,0xbc,0xb6,0xda,0x21,0x10,0xff,0xf3,0xd2,
    0xcd,0x0c,0x13,0xec,0x5f,0x97,0x44,0x17,0xc4,0xa7,0x7e,0x3d,0x64,0x5d,0x19,0x73,
    0x60,0x81,0x4f,0xdc,0x22,0x2a,0x90,0x88,0x46,0xee,0xb8,0x14,0xde,0x5e,0x0b,0xdb,
    0xe0,0x32,0x3a,0x0a,0x49,0x06,0x24,0x5c,0xc2,0xd3,0xac,0x62,0x91,0x95,0xe4,0x79,
    0xe7,0xc8,0x37,0x6d,0x8d,0xd5,0x4e,0xa9,0x6c,0x56,0xf4,0xea,0x65,0x7a,0xae,0x08,
    0xba,0x78,0x25,0x2e,0x1c,0xa6,0xb4,0xc6,0xe8,0xdd,0x74,0x1f,0x4b,0xbd,0x8b,0x8a,
    0x70,0x3e,0xb5,0x66,0x48,0x03,0xf6,0x0e,0x61,0x35,0x57,0xb9,0x86,0xc1,0x1d,0x9e,
    0xe1,0xf8,0x98,0x11,0x69,0xd9,0x8e,0x94,0x9b,0x1e,0x87,0xe9,0xce,0x55,0x28,0xdf,
    0x8c,0xa1,0x89,0x0d,0xbf,0xe6,0x42,0x68,0x41,0x99,0x2d,0x0f,0xb0,0x54,0xbb,0x16
};

/*
 * Inverse S-box
 */
static const uint8_t inv_sbox[256] = {
    0x52,0x09,0x6a,0xd5,0x30,0x36,0xa5,0x38,0xbf,0x40,0xa3,0x9e,0x81,0xf3,0xd7,0xfb,
    0x7c,0xe3,0x39,0x82,0x9b,0x2f,0xff,0x87,0x34,0x8e,0x43,0x44,0xc4,0xde,0xe9,0xcb,
    0x54,0x7b,0x94,0x32,0xa6,0xc2,0x23,0x3d,0xee,0x4c,0x95,0x0b,0x42,0xfa,0xc3,0x4e,
    0x08,0x2e,0xa1,0x66,0x28,0xd9,0x24,0xb2,0x76,0x5b,0xa2,0x49,0x6d,0x8b,0xd1,0x25,
    0x72,0xf8,0xf6,0x64,0x86,0x68,0x98,0x16,0xd4,0xa4,0x5c,0xcc,0x5d,0x65,0xb6,0x92,
    0x6c,0x70,0x48,0x50,0xfd,0xed,0xb9,0xda,0x5e,0x15,0x46,0x57,0xa7,0x8d,0x9d,0x84,
    0x90,0xd8,0xab,0x00,0x8c,0xbc,0xd3,0x0a,0xf7,0xe4,0x58,0x05,0xb8,0xb3,0x45,0x06,
    0xd0,0x2c,0x1e,0x8f,0xca,0x3f,0x0f,0x02,0xc1,0xaf,0xbd,0x03,0x01,0x13,0x8a,0x6b,
    0x3a,0x91,0x11,0x41,0x4f,0x67,0xdc,0xea,0x97,0xf2,0xcf,0xce,0xf0,0xb4,0xe6,0x73,
    0x96,0xac,0x74,0x22,0xe7,0xad,0x35,0x85,0xe2,0xf9,0x37,0xe8,0x1c,0x75,0xdf,0x6e,
    0x47,0xf1,0x1a,0x71,0x1d,0x29,0xc5,0x89,0x6f,0xb7,0x62,0x0e,0xaa,0x18,0xbe,0x1b,
    0xfc,0x56,0x3e,0x4b,0xc6,0xd2,0x79,0x20,0x9a,0xdb,0xc0,0xfe,0x78,0xcd,0x5a,0xf4,
    0x1f,0xdd,0xa8,0x33,0x88,0x07,0xc7,0x31,0xb1,0x12,0x10,0x59,0x27,0x80,0xec,0x5f,
    0x60,0x51,0x7f,0xa9,0x19,0xb5,0x4a,0x0d,0x2d,0xe5,0x7a,0x9f,0x93,0xc9,0x9c,0xef,
    0xa0,0xe0,0x3b,0x4d,0xae,0x2a,0xf5,0xb0,0xc8,0xeb,0xbb,0x3c,0x83,0x53,0x99,0x61,
    0x17,0x2b,0x04,0x7e,0xba,0x77,0xd6,0x26,0xe1,0x69,0x14,0x63,0x55,0x21,0x0c,0x7d
};

static const uint8_t rcon[15] = {
    0x00,0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x1B,0x36,0x6C,0xD8,0xAB,0x4D
};


static inline uint8_t xtime(uint8_t x)
{
    return (uint8_t)((x << 1) ^ ((x & 0x80) ? 0x1B : 0));
}

static inline uint8_t mul(uint8_t a, uint8_t b)
{
    uint8_t r = 0;
    while (b)
    {
        if (b & 1) r ^= a;
        a = xtime(a);
        b >>= 1;
    }
    return r;
}

static void tx_add_round_key(uint8_t state[16], const uint8_t *roundKey)
{
    for (int i = 0; i < 16; i++)
    {
        state[i] ^= roundKey[i];
    }
}

static void tx_sub_bytes(uint8_t state[16])
{
    for (int i = 0; i < 16; i++)
    {
        state[i] = sbox[state[i]];
    }
}

static void tx_inverse_sub_bytes(uint8_t state[16])
{
    for (int i=0;i<16;i++)
    {
        state[i] = inv_sbox[state[i]];
    }
}

static void tx_shift_rows(uint8_t s[16]) {

    // TODO: Rewrite this.
    uint8_t t[16];
    t[0]=s[0];   t[4]=s[4];   t[8]=s[8];   t[12]=s[12];
    t[1]=s[5];   t[5]=s[9];   t[9]=s[13];  t[13]=s[1];
    t[2]=s[10];  t[6]=s[14];  t[10]=s[2];  t[14]=s[6];
    t[3]=s[15];  t[7]=s[3];   t[11]=s[7];  t[15]=s[11];

    memcpy(s, t, 16);
}

static void tx_inverse_shift_rows(uint8_t s[16]) {
    uint8_t t[16];
    t[0]=s[0];   t[4]=s[4];   t[8]=s[8];   t[12]=s[12];
    t[1]=s[13];  t[5]=s[1];   t[9]=s[5];   t[13]=s[9];
    t[2]=s[10];  t[6]=s[14];  t[10]=s[2];  t[14]=s[6];
    t[3]=s[7];   t[7]=s[11];  t[11]=s[15]; t[15]=s[3];
    memcpy(s, t, 16);
}

static void tx_mix_columns(uint8_t s[16]) {
    for (int c = 0; c < 4; c++)
    {
        uint8_t *col = s + 4*c;
        uint8_t a0=col[0];
        uint8_t a1=col[1];
        uint8_t a2=col[2];
        uint8_t a3=col[3];

        col[0] = (uint8_t)(mul(a0, 2) ^ mul(a1, 3) ^ a2 ^ a3);
        col[1] = (uint8_t)(a0 ^ mul(a1, 2) ^ mul(a2, 3) ^ a3);
        col[2] = (uint8_t)(a0 ^ a1 ^ mul(a2, 2) ^ mul(a3, 3));
        col[3] = (uint8_t)(mul(a0, 3) ^ a1 ^ a2 ^ mul(a3, 2));
    }
}

static void tx_inverse_mix_columns(uint8_t s[16]) {
    for (int c = 0; c < 4; c++)
    {
        uint8_t *col = s + 4 * c;
        uint8_t a0 = col[0];
        uint8_t a1 = col[1];
        uint8_t a2 = col[2];
        uint8_t a3 = col[3];

        col[0] = (uint8_t)(mul(a0, 14) ^ mul(a1, 11) ^ mul(a2, 13) ^ mul(a3, 9));
        col[1] = (uint8_t)(mul(a0, 9)  ^ mul(a1, 14) ^ mul(a2, 11) ^ mul(a3, 13));
        col[2] = (uint8_t)(mul(a0, 13) ^ mul(a1, 9)  ^ mul(a2, 14) ^ mul(a3, 11));
        col[3] = (uint8_t)(mul(a0, 11) ^ mul(a1, 13) ^ mul(a2, 9)  ^ mul(a3, 14));
    }
}

void aes256_key_expansion(const uint8_t key[32], uint8_t roundKeys[AES_EXPANDED_KEY_SIZE]) {
    uint32_t w[60];

    for (int i = 0; i < 8; i++)
    {
        w[i] = (key[4 * i] << 24) | (key[4 * i + 1] << 16) | (key[4 * i + 2] << 8) | key[4 * i + 3];
    }

    for (int i = 8; i < 60; i++)
    {
        uint32_t temp = w[i - 1];

        if (i % 8 == 0)
        {
            uint8_t t[4] = {
                (temp >> 16) & 0xff,
                (temp >>  8) & 0xff,
                (temp >>  0) & 0xff,
                (temp >> 24) & 0xff
            };
            t[0] = sbox[t[0]];
            t[1] = sbox[t[1]];
            t[2] = sbox[t[2]];
            t[3] = sbox[t[3]];
            temp = (t[0] << 24) | (t[1] << 16) | (t[2] << 8) | t[3];
            temp ^= (rcon[i / 8] << 24);
        }
        else if (i % 8 == 4)
        {
            uint8_t t[4] = {
                (temp >> 24) & 0xff,
                (temp >> 16) & 0xff,
                (temp >>  8) & 0xff,
                (temp >>  0) & 0xff
            };
            t[0] = sbox[t[0]];
            t[1] = sbox[t[1]];
            t[2] = sbox[t[2]];
            t[3] = sbox[t[3]];
            temp = (t[0] << 24) | (t[1] << 16) | (t[2] << 8) | t[3];
        }

        w[i] = w[i - 8] ^ temp;
    }

    for (int i = 0; i < 60; i++)
    {
        roundKeys[4 * i + 0] = (uint8_t)(w[i] >> 24);
        roundKeys[4 * i + 1] = (uint8_t)(w[i] >> 16);
        roundKeys[4 * i + 2] = (uint8_t)(w[i] >> 8);
        roundKeys[4 * i + 3] = (uint8_t)(w[i]);
    }
}

void aes256_encrypt_block(const uint8_t key[32], const uint8_t in[16], uint8_t out[16])
{
    uint8_t state[16];
    uint8_t round_key[AES_EXPANDED_KEY_SIZE];

    memcpy(state, in, 16);
    aes256_key_expansion(key, round_key);
    tx_add_round_key(state, round_key);

    for (int r = 1; r < AES_256_ROUNDS; r++)
    {
        tx_sub_bytes(state);
        tx_shift_rows(state);
        tx_mix_columns(state);
        tx_add_round_key(state, round_key + 16 * r);
    }

    tx_sub_bytes(state);
    tx_shift_rows(state);
    tx_add_round_key(state, round_key + 16 * AES_256_ROUNDS);

    memcpy(out, state, 16);
}

void aes256_decrypt_block(const uint8_t key[32], const uint8_t in[16], uint8_t out[16])
{
    uint8_t state[16];
    uint8_t round_key[AES_EXPANDED_KEY_SIZE];
    memcpy(state, in, 16);
    aes256_key_expansion(key, round_key);

    tx_add_round_key(state, round_key + 16 * AES_256_ROUNDS);

    for (int r = AES_256_ROUNDS - 1; r > 0; r--)
    {
        tx_inverse_shift_rows(state);
        tx_inverse_sub_bytes(state);
        tx_add_round_key(state, round_key + 16 * r);
        tx_inverse_mix_columns(state);
    }

    tx_inverse_shift_rows(state);
    tx_inverse_sub_bytes(state);
    tx_add_round_key(state, round_key);

    memcpy(out, state, 16);
}

void* aes256_encrypt_buffer (const uint8_t key[32], const void* buffer, size_t size, size_t* result_sz)
{
    int r = size % 16;
    size_t padding_size = r == 0 ? 0 : 16 - r;
    size_t output_size = size + padding_size;
    if (result_sz)
    {
        *result_sz = output_size;
    }
    uint8_t* padded_input = (uint8_t*) calloc(output_size, sizeof(uint8_t));
    if (!padded_input)
    {
        return NULL;
    }

    uint8_t* output = (uint8_t*) calloc(output_size, sizeof(uint8_t));
    if (!output)
    {
        goto free_input;
        return NULL;
    }

    memcpy(padded_input, buffer, size); // relies on calloc() setting padded bytes to zero

    for (int i = 0; i < output_size; i += 16)
    {
        uint8_t* in = padded_input + i;
        uint8_t* out = output + i;
        aes256_encrypt_block(key, in, out);
    }


free_input:
    free(padded_input);
    return output;
}

void* aes256_decrypt_buffer (const uint8_t key[32], const void* buffer, size_t size)
{
    if (size % 16 != 0)
    {
        return NULL;
    }

    uint8_t* output = (uint8_t*) calloc(size, sizeof(uint8_t));
    if (!output)
    {
        return NULL;
    }

    uint8_t* input = (uint8_t*) buffer;

    for (int i = 0; i < size; i += 16)
    {
        uint8_t* in = input + i;
        uint8_t* out = output + i;
        aes256_decrypt_block(key, in, out);
    }

    return output;
}

void aes256_initialize_key (uint8_t key[32], int seed)
{
    memset(key, 0, sizeof(uint8_t) * 32);
    srand(seed);
    for (int i = 0; i < 32; i++)
    {
        key[i] = rand() % 256;
    }
}

