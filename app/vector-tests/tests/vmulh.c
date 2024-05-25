// Copyright 2021 ETH Zurich and University of Bologna.
// Solderpad Hardware License, Version 0.51, see LICENSE for details.
// SPDX-License-Identifier: SHL-0.51
//
// Author: Matteo Perotti <mperotti@iis.ee.ethz.ch>
//         Basile Bougenot <bbougenot@student.ethz.ch>

#include "vector_macros.h"

void TEST_CASE1(void) {
  VSET(16, e8, m1);
  VLOAD_8(v2, 0xc2, 0xf6, 0xad, 0x0f, 0xc6, 0xeb, 0xca, 0xf3, 0xf3, 0xd9, 0xf4,
          0xf6, 0x27, 0x57, 0x4f, 0xef);
  VLOAD_8(v3, 0xf9, 0x0c, 0xa8, 0x05, 0x23, 0xff, 0x48, 0x74, 0xd4, 0x6b, 0x5b,
          0x07, 0x8b, 0x2e, 0x9e, 0x5f);
  asm volatile("vmulh.vv v1, v2, v3");
  VCMP_I8(1, v1, 0x01, 0xff, 0x1c, 0x00, 0xf8, 0x00, 0xf0, 0xfa, 0x02, 0xef,
          0xfb, 0xff, 0xee, 0x0f, 0xe1, 0xf9);

  VSET(16, e16, m1);
  VLOAD_16(v2, 0x911a, 0x9f44, 0x3d2a, 0xa2a8, 0x5aae, 0x0231, 0x56fa, 0xb8b8,
           0x55df, 0x8a78, 0x413c, 0xeb32, 0x6bc4, 0x3e47, 0x3d79, 0x2c8f);
  VLOAD_16(v3, 0x89fd, 0x6bb7, 0x4a94, 0x770c, 0x7c87, 0x8b01, 0xbb6a, 0x900d,
           0xb589, 0x709e, 0xc75d, 0xafa5, 0x4fd5, 0x2d77, 0x8dbf, 0x3a0a);
  asm volatile("vmulh.vv v1, v2, v3");
  VCMP_I16(2, v1, 0x331f, 0xd74c, 0x11d1, 0xd497, 0x2c1c, 0xfeff, 0xe8b2,
           0x1f2b, 0xe705, 0xcc4b, 0xf191, 0x0687, 0x219b, 0x0b0f, 0xe490,
           0x0a1a);

  VSET(16, e32, m1);
  VLOAD_32(v2, 0xc66253f4, 0x710c314c, 0xa6fe579b, 0xa7947b70, 0xbf94259f,
           0x211088fe, 0x64bfd390, 0x1d49c8d8, 0x7a12a08a, 0x190ee9ae,
           0x361172f8, 0x52457515, 0x05d4b17b, 0x7bb6d43b, 0x96270cc7,
           0x62d35f88);
  VLOAD_32(v3, 0xd14a266e, 0xe4f43ca5, 0x1c067312, 0xa1909d51, 0x35b8d1aa,
           0xdcd3e2ea, 0x05cec46d, 0xbe70ebd4, 0xe15e49c5, 0x81be068b,
           0x49fd9ad8, 0x6c2a5abd, 0x26216dd6, 0x9e3188ac, 0x14af13c4,
           0xd98c6d7f);
  asm volatile("vmulh.vv v1, v2, v3");
  VCMP_I32(3, v1, 0x0a83425c, 0xf40e8502, 0xf6419389, 0x209df360, 0xf27b2982,
           0xfb750aac, 0x02491ecb, 0xf87fe57b, 0xf164b493, 0xf3a433c8,
           0x0fa089bb, 0x22c2e9f3, 0x00de5543, 0xd0bbf2cc, 0xf772a985,
           0xf128024f);

//   VSET(16, e64, m1);
//   VLOAD_64(v2, 0x9def74822cdf1a42, 0x29307e854b225449, 0x071cdf51785d150e,
//            0xe8ced2e9009d363f, 0xa88c741be4e81893, 0x4a7655ec12afe587,
//            0x50c5efa017138cb9, 0x88e076b6ef49619d, 0x5745683769adf333,
//            0x5b3b01f4b1c4fd42, 0x8a3d55e48864d144, 0x2eac97fae4174cac,
//            0xdb8804ccf6f55686, 0xf7bea87bac575241, 0x250ed7ddade1432d,
//            0x06ae542295f32453);
//   VLOAD_64(v3, 0xc5c41e47b5f3de5f, 0xa03833fb95a7e7e2, 0x74f0573dba05b058,
//            0x687968e9ba2a98ad, 0x29f4aaf3e5e4f2b6, 0x2c40a650d53f6f08,
//            0x491da2c816388b78, 0x2822d8207421ec15, 0x5dd8d394b292512a,
//            0x4169844eea56920d, 0x97183b6e1e85fd70, 0x224077bf8899614c,
//            0x3a9c0520417d4f32, 0xee47b09a33f49fca, 0x3f9f1140fbd02e0a,
//            0x6106ad88eabfc3e2);
//   asm volatile("vmulh.vv v1, v2, v3");
//   VCMP_I64(4, v1, 0x164eafe1cab0639c, 0xf096db86d4d06824, 0x033fc2aecddc0dd7,
//            0xf68905ef31703000, 0xf1aaea11162383ae, 0x0cdf24ba4cf3be38,
//            0x1711cb1d2f008de9, 0xed52dbcaa3de5ca2, 0x1ffe218cf60b6bf9,
//            0x174f95d97aff7bf9, 0x3041b22ecc97909a, 0x063ead2a7756c9da,
//            0xf7a6973e6c9e5ce6, 0x0092485623082173, 0x0935add704f8cec8,
//            0x02883a7e75391040);
};

void TEST_CASE2(void) {
  VSET(16, e8, m1);
  VLOAD_8(v2, 0xc2, 0xf6, 0xad, 0x0f, 0xc6, 0xeb, 0xca, 0xf3, 0xf3, 0xd9, 0xf4,
          0xf6, 0x27, 0x57, 0x4f, 0xef);
  VLOAD_8(v3, 0xf9, 0x0c, 0xa8, 0x05, 0x23, 0xff, 0x48, 0x74, 0xd4, 0x6b, 0x5b,
          0x07, 0x8b, 0x2e, 0x9e, 0x5f);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v1);
  asm volatile("vmulh.vv v1, v2, v3, v0.t");
  VCMP_I8(5, v1, 0, 0xff, 0, 0x00, 0, 0x00, 0, 0xfa, 0, 0xef, 0, 0xff, 0, 0x0f,
          0, 0xf9);

  VSET(16, e16, m1);
  VLOAD_16(v2, 0x911a, 0x9f44, 0x3d2a, 0xa2a8, 0x5aae, 0x0231, 0x56fa, 0xb8b8,
           0x55df, 0x8a78, 0x413c, 0xeb32, 0x6bc4, 0x3e47, 0x3d79, 0x2c8f);
  VLOAD_16(v3, 0x89fd, 0x6bb7, 0x4a94, 0x770c, 0x7c87, 0x8b01, 0xbb6a, 0x900d,
           0xb589, 0x709e, 0xc75d, 0xafa5, 0x4fd5, 0x2d77, 0x8dbf, 0x3a0a);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v1);
  asm volatile("vmulh.vv v1, v2, v3, v0.t");
  VCMP_I16(6, v1, 0, 0xd74c, 0, 0xd497, 0, 0xfeff, 0, 0x1f2b, 0, 0xcc4b, 0,
           0x0687, 0, 0x0b0f, 0, 0x0a1a);

  VSET(16, e32, m1);
  VLOAD_32(v2, 0xc66253f4, 0x710c314c, 0xa6fe579b, 0xa7947b70, 0xbf94259f,
           0x211088fe, 0x64bfd390, 0x1d49c8d8, 0x7a12a08a, 0x190ee9ae,
           0x361172f8, 0x52457515, 0x05d4b17b, 0x7bb6d43b, 0x96270cc7,
           0x62d35f88);
  VLOAD_32(v3, 0xd14a266e, 0xe4f43ca5, 0x1c067312, 0xa1909d51, 0x35b8d1aa,
           0xdcd3e2ea, 0x05cec46d, 0xbe70ebd4, 0xe15e49c5, 0x81be068b,
           0x49fd9ad8, 0x6c2a5abd, 0x26216dd6, 0x9e3188ac, 0x14af13c4,
           0xd98c6d7f);
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v1);
  asm volatile("vmulh.vv v1, v2, v3, v0.t");
  VCMP_I32(7, v1, 0, 0xf40e8502, 0, 0x209df360, 0, 0xfb750aac, 0, 0xf87fe57b, 0,
           0xf3a433c8, 0, 0x22c2e9f3, 0, 0xd0bbf2cc, 0, 0xf128024f);

//   VSET(16, e64, m1);
//   VLOAD_64(v2, 0x9def74822cdf1a42, 0x29307e854b225449, 0x071cdf51785d150e,
//            0xe8ced2e9009d363f, 0xa88c741be4e81893, 0x4a7655ec12afe587,
//            0x50c5efa017138cb9, 0x88e076b6ef49619d, 0x5745683769adf333,
//            0x5b3b01f4b1c4fd42, 0x8a3d55e48864d144, 0x2eac97fae4174cac,
//            0xdb8804ccf6f55686, 0xf7bea87bac575241, 0x250ed7ddade1432d,
//            0x06ae542295f32453);
//   VLOAD_64(v3, 0xc5c41e47b5f3de5f, 0xa03833fb95a7e7e2, 0x74f0573dba05b058,
//            0x687968e9ba2a98ad, 0x29f4aaf3e5e4f2b6, 0x2c40a650d53f6f08,
//            0x491da2c816388b78, 0x2822d8207421ec15, 0x5dd8d394b292512a,
//            0x4169844eea56920d, 0x97183b6e1e85fd70, 0x224077bf8899614c,
//            0x3a9c0520417d4f32, 0xee47b09a33f49fca, 0x3f9f1140fbd02e0a,
//            0x6106ad88eabfc3e2);
//   VLOAD_8(v0, 0xAA, 0xAA);
//   VCLEAR(v1);
//   asm volatile("vmulh.vv v1, v2, v3, v0.t");
//   VCMP_I64(8, v1, 0, 0xf096db86d4d06824, 0, 0xf68905ef31703000, 0,
//            0x0cdf24ba4cf3be38, 0, 0xed52dbcaa3de5ca2, 0, 0x174f95d97aff7bf9, 0,
//            0x063ead2a7756c9da, 0, 0x0092485623082173, 0, 0x02883a7e75391040);
};

void TEST_CASE3(void) {
  VSET(16, e8, m1);
  VLOAD_8(v2, 0x92, 0xce, 0xdd, 0x64, 0x60, 0x29, 0xa6, 0xd5, 0x07, 0x8c, 0x71,
          0x94, 0x95, 0xf6, 0xd4, 0xbd);
  int64_t scalar = 5;
  asm volatile("vmulh.vx v1, v2, %[A]" ::[A] "r"(scalar));
  VCMP_I8(9, v1, 0xfd, 0xff, 0xff, 0x01, 0x01, 0x00, 0xfe, 0xff, 0x00, 0xfd,
          0x02, 0xfd, 0xfd, 0xff, 0xff, 0xfe);

  VSET(16, e16, m1);
  VLOAD_16(v2, 0x3b9b, 0x7758, 0x030f, 0x9f60, 0x13e2, 0x8f0d, 0xfc9d, 0x3922,
           0x3a43, 0x58b5, 0xb9e9, 0xa4e8, 0x4bac, 0x5636, 0x9f4a, 0xbd52);
  scalar = -5383;
  asm volatile("vmulh.vx v1, v2, %[A]" ::[A] "r"(scalar));
  VCMP_I16(10, v1, 0xfb1a, 0xf632, 0xffbf, 0x07ef, 0xfe5d, 0x0947, 0x0047,
           0xfb4e, 0xfb36, 0xf8b6, 0x05c1, 0x077b, 0xf9c8, 0xf8eb, 0x07f1,
           0x057a);

  VSET(16, e32, m1);
  VLOAD_32(v2, 0x7efca225, 0xdbc0a9ca, 0x0cf02cf8, 0xc19bdc84, 0x7fa3ca90,
           0x3d878c29, 0x15809928, 0x7b0b7421, 0x48b872f5, 0xafbfeab4,
           0xe79dc9ba, 0xe60a8fc0, 0x1fd7e866, 0xed7df17c, 0x0684a7ee,
           0xb2b01a61);
  scalar = 6474219;
  asm volatile("vmulh.vx v1, v2, %[A]" ::[A] "r"(scalar));
  VCMP_I32(11, v1, 0x003100de, 0xfff20329, 0x0004fe25, 0xffe7ec74, 0x00314160,
           0x0017be6b, 0x00084c30, 0x002f7b6f, 0x001c0ff7, 0xffe1082b,
           0xfff6972b, 0xfff5fb91, 0x000c49c4, 0xfff8db9d, 0x000283ec,
           0xffe22a6f);

//   VSET(16, e64, m1);
//   VLOAD_64(v2, 0x42e9b386e7453715, 0xd6aae3fda4b2f3e8, 0xfcbec1ad7996a0b2,
//            0x4fcb68f516b589c9, 0x414b0eeb29c35e62, 0x038c6221829f4241,
//            0xf2c2c11f26e326b0, 0xed9ad0ce4d50a009, 0xc57105a57d435897,
//            0x90c1615935c1abd0, 0xf5b41f9a0a988065, 0xb09790bdcbecee7b,
//            0x1d9da4f87df33b54, 0xe347aadb53bdc879, 0x7a39a7269cbae2a7,
//            0x422ed2952e246f26);
//   scalar = -598189234597999223;
//   asm volatile("vmulh.vx v1, v2, %[A]" ::[A] "r"(scalar));
//   VCMP_I64(12, v1, 0xfdd4850b300f6008, 0x01571f899f226d57, 0x001b0534decdc9a2,
//            0xfd6994f8de6e51aa, 0xfde1f73873e6758a, 0xffe28b043b9b8971,
//            0x006de7f819baba3d, 0x0098b57f65f599e1, 0x01e62040839e971b,
//            0x039b807e6f36fd81, 0x005579d7e0c206af, 0x0293356120e5cee9,
//            0xff0a24a69d9af87b, 0x00ee6bb505683322, 0xfc095797a6198143,
//            0xfdda946cdb2f169c);
};

void TEST_CASE4(void) {
  VSET(16, e8, m1);
  VLOAD_8(v2, 0x92, 0xce, 0xdd, 0x64, 0x60, 0x29, 0xa6, 0xd5, 0x07, 0x8c, 0x71,
          0x94, 0x95, 0xf6, 0xd4, 0xbd);
  int64_t scalar = 5;
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v1);
  asm volatile("vmulh.vx v1, v2, %[A], v0.t" ::[A] "r"(scalar));
  VCMP_I8(13, v1, 0, 0xff, 0, 0x01, 0, 0x00, 0, 0xff, 0, 0xfd, 0, 0xfd, 0, 0xff,
          0, 0xfe);

  VSET(16, e16, m1);
  VLOAD_16(v2, 0x3b9b, 0x7758, 0x030f, 0x9f60, 0x13e2, 0x8f0d, 0xfc9d, 0x3922,
           0x3a43, 0x58b5, 0xb9e9, 0xa4e8, 0x4bac, 0x5636, 0x9f4a, 0xbd52);
  scalar = -5383;
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v1);
  asm volatile("vmulh.vx v1, v2, %[A], v0.t" ::[A] "r"(scalar));
  VCMP_I16(14, v1, 0, 0xf632, 0, 0x07ef, 0, 0x0947, 0, 0xfb4e, 0, 0xf8b6, 0,
           0x077b, 0, 0xf8eb, 0, 0x057a);

  VSET(16, e32, m1);
  VLOAD_32(v2, 0x7efca225, 0xdbc0a9ca, 0x0cf02cf8, 0xc19bdc84, 0x7fa3ca90,
           0x3d878c29, 0x15809928, 0x7b0b7421, 0x48b872f5, 0xafbfeab4,
           0xe79dc9ba, 0xe60a8fc0, 0x1fd7e866, 0xed7df17c, 0x0684a7ee,
           0xb2b01a61);
  scalar = 6474219;
  VLOAD_8(v0, 0xAA, 0xAA);
  VCLEAR(v1);
  asm volatile("vmulh.vx v1, v2, %[A], v0.t" ::[A] "r"(scalar));
  VCMP_I32(15, v1, 0, 0xfff20329, 0, 0xffe7ec74, 0, 0x0017be6b, 0, 0x002f7b6f,
           0, 0xffe1082b, 0, 0xfff5fb91, 0, 0xfff8db9d, 0, 0xffe22a6f);

//   VSET(16, e64, m1);
//   VLOAD_64(v2, 0x42e9b386e7453715, 0xd6aae3fda4b2f3e8, 0xfcbec1ad7996a0b2,
//            0x4fcb68f516b589c9, 0x414b0eeb29c35e62, 0x038c6221829f4241,
//            0xf2c2c11f26e326b0, 0xed9ad0ce4d50a009, 0xc57105a57d435897,
//            0x90c1615935c1abd0, 0xf5b41f9a0a988065, 0xb09790bdcbecee7b,
//            0x1d9da4f87df33b54, 0xe347aadb53bdc879, 0x7a39a7269cbae2a7,
//            0x422ed2952e246f26);
//   scalar = -598189234597999223;
//   VLOAD_8(v0, 0xAA, 0xAA);
//   VCLEAR(v1);
//   asm volatile("vmulh.vx v1, v2, %[A], v0.t" ::[A] "r"(scalar));
//   VCMP_I64(16, v1, 0, 0x01571f899f226d57, 0, 0xfd6994f8de6e51aa, 0,
//            0xffe28b043b9b8971, 0, 0x0098b57f65f599e1, 0, 0x039b807e6f36fd81, 0,
//            0x0293356120e5cee9, 0, 0x00ee6bb505683322, 0, 0xfdda946cdb2f169c);
};

int main(void) {
  INIT_CHECK();
  enable_vec();

  TEST_CASE1();
  TEST_CASE2();
  TEST_CASE3();
  TEST_CASE4();

  EXIT_CHECK();
}
