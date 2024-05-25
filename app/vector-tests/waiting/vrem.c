// Copyright 2021 ETH Zurich and University of Bologna.
// Solderpad Hardware License, Version 0.51, see LICENSE for details.
// SPDX-License-Identifier: SHL-0.51
//
// Author: Matteo Perotti <mperotti@iis.ee.ethz.ch>
//         Basile Bougenot <bbougenot@student.ethz.ch>

#include "vector_macros.h"

void TEST_CASE1(void) {
  VSET(16, e8, m1);
  VLOAD_8(v2, 0x9b, 0x28, 0xec, 0x86, 0x26, 0x85, 0xf7, 0x33, 0x46, 0x37, 0x2c,
          0x0c, 0x8e, 0xae, 0xa1, 0x93);
  VLOAD_8(v3, 0x84, 0x5e, 0x3b, 0xdf, 0x10, 0xfc, 0x05, 0xcf, 0x42, 0xbe, 0x23,
          0xdb, 0x37, 0x78, 0xe2, 0x85);
  asm volatile("vrem.vv v1, v2, v3");
  VCMP_I8(1, v1, 0x9b, 0x28, 0xec, 0xe9, 0x06, 0xfd, 0xfc, 0x02, 0x04, 0x37,
          0x09, 0x0c, 0xfc, 0xae, 0xfb, 0x93);

  VSET(16, e16, m1);
  VLOAD_16(v2, 0xb58f, 0xa184, 0xdcf9, 0xd084, 0xbbc6, 0xcf0e, 0xbbd4, 0xa20c,
           0xe04c, 0xd954, 0xda74, 0xa394, 0x207a, 0x8975, 0xddd3, 0x897d);
  VLOAD_16(v3, 0x4534, 0xafd7, 0xf703, 0x92c2, 0x97e3, 0xd85a, 0x1540, 0x8c5c,
           0x4a71, 0x43a7, 0xe65d, 0x2bdc, 0x497b, 0x6aa0, 0x6071, 0xf431);
  asm volatile("vrem.vv v1, v2, v3");
  VCMP_I16(2, v1, 0xfac3, 0xf1ad, 0xf7f0, 0xd084, 0xbbc6, 0xf6b4, 0xfb94,
           0xa20c, 0xe04c, 0xd954, 0xf417, 0xfb4c, 0x207a, 0xf415, 0xddd3,
           0xff93);

  VSET(16, e32, m1);
  VLOAD_32(v2, 0x620db972, 0x60b1f870, 0x7d1badcf, 0x90a85eb6, 0xca41954b,
           0x10dc3772, 0xf7749e82, 0x027ed4d3, 0xdcb6a562, 0xa979baf0,
           0xb480c184, 0x979555c6, 0x3f894108, 0x803bd362, 0x9038beec,
           0x22d7ca24);
  VLOAD_32(v3, 0xb9b52c0c, 0x30b52d8c, 0x832f89ea, 0x95181d9c, 0x85a6a24f,
           0x2f2c64a7, 0xebe4120c, 0x83852646, 0xfb1857b5, 0x25400571,
           0xab2d7393, 0xddb87ac8, 0x01149cdf, 0x62b2c8dc, 0xaed39563,
           0x41ec046e);
  asm volatile("vrem.vv v1, v2, v3");
  VCMP_I32(3, v1, 0x1bc2e57e, 0x2ffccae4, 0x004b37b9, 0xfb90411a, 0xca41954b,
           0x10dc3772, 0xf7749e82, 0x027ed4d3, 0xff0c3f6f, 0xf3f9c5d2,
           0xb480c184, 0xfe6be56e, 0x00ddb682, 0xe2ee9c3e, 0xe1652989,
           0x22d7ca24);

//   VSET(16, e64, m1);
//   VLOAD_64(v2, 0x9fc0a4e82116b913, 0xbd1a679edd2667e1, 0x559913931b91caf2,
//            0xecfe6fb53a8b043d, 0xd8a48a111d080e66, 0x7baccec6b5a29e3e,
//            0x8746dc00d1d7ff0b, 0x467babd497d4931b, 0x6f7f3e669faa900c,
//            0x36e81d34c3ee3445, 0x99bcc4a480c648c5, 0xc8ae527a2cc4d908,
//            0xce3b4c1da847fe6a, 0x3709710bc016c1fc, 0x81471426bbe09e45,
//            0x0f0389282729456f);
//   VLOAD_64(v3, 0xf2473f877dd9c3df, 0xd2471da7c8ff8466, 0x7e93451b38765d03,
//            0xf7e905f27777369f, 0x73cbef014fd0f311, 0x4c3e4fc36800b443,
//            0x4c283e06a5067444, 0xdc8295e57f30e905, 0x08207a363067024e,
//            0x42aba773f21efc47, 0x5f00e9093d50b50f, 0x5ff0dcd41bf799fa,
//            0xe8c1d1110518742a, 0x34fe1a3555bf07f0, 0xd1bce4800f79700f,
//            0xff00f7d87b2c7068);
//   asm volatile("vrem.vv v1, v2, v3");
//   VCMP_I64(4, v1, 0xffcde833b0225dfa, 0xead349f71426e37b, 0x559913931b91caf2,
//            0xfd2c63d04b9c96ff, 0xd8a48a111d080e66, 0x2f6e7f034da1e9fb,
//            0xd36f1a0776de734f, 0x22fe41ba17057c20, 0x05d909a62a6f7216,
//            0x36e81d34c3ee3445, 0xf8bdadadbe16fdd4, 0xc8ae527a2cc4d908,
//            0xfcb7a9fb9e171616, 0x020b56d66a57ba0c, 0xddcd4b269cedbe27,
//            0x00120ed75ec3db87);
};

void TEST_CASE2(void) {
//   VSET(16, e8, m1);
//   VLOAD_8(v2, 0x9b, 0x28, 0xec, 0x86, 0x26, 0x85, 0xf7, 0x33, 0x46, 0x37, 0x2c,
//           0x0c, 0x8e, 0xae, 0xa1, 0x93);
//   VLOAD_8(v3, 0x84, 0x5e, 0x3b, 0xdf, 0x10, 0xfc, 0x05, 0xcf, 0x42, 0xbe, 0x23,
//           0xdb, 0x37, 0x78, 0xe2, 0x85);
//   VLOAD_8(v0, 0xAA, 0xAA);
//   VCLEAR(v1);
//   asm volatile("vrem.vv v1, v2, v3, v0.t");
//   VCMP_I8(5, v1, 0, 0x28, 0, 0xe9, 0, 0xfd, 0, 0x02, 0, 0x37, 0, 0x0c, 0, 0xae,
//           0, 0x93);

//   VSET(16, e16, m1);
//   VLOAD_16(v2, 0xb58f, 0xa184, 0xdcf9, 0xd084, 0xbbc6, 0xcf0e, 0xbbd4, 0xa20c,
//            0xe04c, 0xd954, 0xda74, 0xa394, 0x207a, 0x8975, 0xddd3, 0x897d);
//   VLOAD_16(v3, 0x4534, 0xafd7, 0xf703, 0x92c2, 0x97e3, 0xd85a, 0x1540, 0x8c5c,
//            0x4a71, 0x43a7, 0xe65d, 0x2bdc, 0x497b, 0x6aa0, 0x6071, 0xf431);
//   VLOAD_8(v0, 0xAA, 0xAA);
//   VCLEAR(v1);
//   asm volatile("vrem.vv v1, v2, v3, v0.t");
//   VCMP_I16(6, v1, 0, 0xf1ad, 0, 0xd084, 0, 0xf6b4, 0, 0xa20c, 0, 0xd954, 0,
//            0xfb4c, 0, 0xf415, 0, 0xff93);

//   VSET(16, e32, m1);
//   VLOAD_32(v2, 0x620db972, 0x60b1f870, 0x7d1badcf, 0x90a85eb6, 0xca41954b,
//            0x10dc3772, 0xf7749e82, 0x027ed4d3, 0xdcb6a562, 0xa979baf0,
//            0xb480c184, 0x979555c6, 0x3f894108, 0x803bd362, 0x9038beec,
//            0x22d7ca24);
//   VLOAD_32(v3, 0xb9b52c0c, 0x30b52d8c, 0x832f89ea, 0x95181d9c, 0x85a6a24f,
//            0x2f2c64a7, 0xebe4120c, 0x83852646, 0xfb1857b5, 0x25400571,
//            0xab2d7393, 0xddb87ac8, 0x01149cdf, 0x62b2c8dc, 0xaed39563,
//            0x41ec046e);
//   VLOAD_8(v0, 0xAA, 0xAA);
//   VCLEAR(v1);
//   asm volatile("vrem.vv v1, v2, v3, v0.t");
//   VCMP_I32(7, v1, 0, 0x2ffccae4, 0, 0xfb90411a, 0, 0x10dc3772, 0, 0x027ed4d3, 0,
//            0xf3f9c5d2, 0, 0xfe6be56e, 0, 0xe2ee9c3e, 0, 0x22d7ca24);

//   VSET(16, e64, m1);
//   VLOAD_64(v2, 0x9fc0a4e82116b913, 0xbd1a679edd2667e1, 0x559913931b91caf2,
//            0xecfe6fb53a8b043d, 0xd8a48a111d080e66, 0x7baccec6b5a29e3e,
//            0x8746dc00d1d7ff0b, 0x467babd497d4931b, 0x6f7f3e669faa900c,
//            0x36e81d34c3ee3445, 0x99bcc4a480c648c5, 0xc8ae527a2cc4d908,
//            0xce3b4c1da847fe6a, 0x3709710bc016c1fc, 0x81471426bbe09e45,
//            0x0f0389282729456f);
//   VLOAD_64(v3, 0xf2473f877dd9c3df, 0xd2471da7c8ff8466, 0x7e93451b38765d03,
//            0xf7e905f27777369f, 0x73cbef014fd0f311, 0x4c3e4fc36800b443,
//            0x4c283e06a5067444, 0xdc8295e57f30e905, 0x08207a363067024e,
//            0x42aba773f21efc47, 0x5f00e9093d50b50f, 0x5ff0dcd41bf799fa,
//            0xe8c1d1110518742a, 0x34fe1a3555bf07f0, 0xd1bce4800f79700f,
//            0xff00f7d87b2c7068);
//   VLOAD_8(v0, 0xAA, 0xAA);
//   VCLEAR(v1);
//   asm volatile("vrem.vv v1, v2, v3, v0.t");
//   VCMP_I64(8, v1, 0, 0xead349f71426e37b, 0, 0xfd2c63d04b9c96ff, 0,
//            0x2f6e7f034da1e9fb, 0, 0x22fe41ba17057c20, 0, 0x36e81d34c3ee3445, 0,
//            0xc8ae527a2cc4d908, 0, 0x020b56d66a57ba0c, 0, 0x00120ed75ec3db87);
};

void TEST_CASE3(void) {
  VSET(16, e8, m1);
  VLOAD_8(v2, 0x5b, 0x3b, 0xc4, 0x95, 0x41, 0x71, 0x9b, 0x67, 0x84, 0x2e, 0x0a,
          0x2a, 0xb2, 0x57, 0xe5, 0x6c);
  int64_t scalar = 5;
  asm volatile("vrem.vx v1, v2, %[A]" ::[A] "r"(scalar));
  VCMP_I8(9, v1, 0x01, 0x04, 0x00, 0xfe, 0x00, 0x03, 0xff, 0x03, 0xfc, 0x01,
          0x00, 0x02, 0xfd, 0x02, 0xfe, 0x03);

  VSET(16, e16, m1);
  VLOAD_16(v2, 0xc670, 0x8f3b, 0x200f, 0x52ea, 0xfdce, 0xcf06, 0x57f1, 0x1936,
           0xb6ec, 0x69e8, 0x0abf, 0x441e, 0xa420, 0x396c, 0xe7c9, 0xa464);
  scalar = -538;
  asm volatile("vrem.vx v1, v2, %[A]" ::[A] "r"(scalar));
  VCMP_I16(10, v1, 0xff2e, 0xfe9d, 0x0089, 0x00f4, 0xffe8, 0xff5c, 0x01c7,
           0x0218, 0xfe60, 0x00d4, 0x003d, 0x00de, 0xfe7e, 0x00ae, 0xfee7,
           0xfec2);

  VSET(16, e32, m1);
  VLOAD_32(v2, 0xf937dbf9, 0x6d855b59, 0x3bd09126, 0xaed11886, 0x6eb6f4bd,
           0x5c639253, 0xca0f2abf, 0x57fec97b, 0x39496099, 0x8bfcdd58,
           0x0f19f6e2, 0x2070c8d4, 0x8c689324, 0x2eecd9d7, 0xe2907e94,
           0xb6cc2d44);
  scalar = 649;
  asm volatile("vrem.vx v1, v2, %[A]" ::[A] "r"(scalar));
  VCMP_I32(11, v1, 0xfffffee4, 0x00000116, 0x00000160, 0xffffffef, 0x00000217,
           0x00000275, 0xfffffea6, 0x000000a9, 0x000000e4, 0xfffffe09,
           0x00000272, 0x0000023c, 0xffffff79, 0x000000ce, 0xffffffb3,
           0xfffffe0e);

//   VSET(16, e64, m1);
//   VLOAD_64(v2, 0x94236504e03e6525, 0x8d219d7afe5b2fb0, 0xc65a0b252860ab73,
//            0x2ca68636bacbc0bb, 0x275575f3e3fea940, 0x8f546251aaad354a,
//            0xb1462969035e0fa7, 0x5c9cdc19273ce111, 0x25a8487741ee75db,
//            0x38819f95e162663e, 0x698d19ce0e74ff8d, 0xb525257a9b5cd972,
//            0xb308a4fe0dcbb2f3, 0xf2fa735abc2db4d0, 0xc73c476461ac3f28,
//            0xb2830c2607bfffcc);
//   scalar = -59223;
//   asm volatile("vrem.vx v1, v2, %[A]" ::[A] "r"(scalar));
//   VCMP_I64(12, v1, 0xffffffffffff299e, 0xffffffffffff1f8a, 0xffffffffffff57aa,
//            0x000000000000cc8c, 0x000000000000416e, 0xffffffffffffcecd,
//            0xffffffffffff7e24, 0x000000000000397b, 0x000000000000bb50,
//            0x0000000000006b00, 0x0000000000004f3f, 0xffffffffffff9a21,
//            0xffffffffffffae24, 0xffffffffffffca84, 0xffffffffffffa7fb,
//            0xffffffffffff84dd);
};

void TEST_CASE4(void) {
//   VSET(16, e8, m1);
//   VLOAD_8(v2, 0x5b, 0x3b, 0xc4, 0x95, 0x41, 0x71, 0x9b, 0x67, 0x84, 0x2e, 0x0a,
//           0x2a, 0xb2, 0x57, 0xe5, 0x6c);
//   int64_t scalar = 5;
//   VLOAD_8(v0, 0xAA, 0xAA);
//   VCLEAR(v1);
//   asm volatile("vrem.vx v1, v2, %[A], v0.t" ::[A] "r"(scalar));
//   VCMP_I8(13, v1, 0, 0x04, 0, 0xfe, 0, 0x03, 0, 0x03, 0, 0x01, 0, 0x02, 0, 0x02,
//           0, 0x03);

//   VSET(16, e16, m1);
//   VLOAD_16(v2, 0xc670, 0x8f3b, 0x200f, 0x52ea, 0xfdce, 0xcf06, 0x57f1, 0x1936,
//            0xb6ec, 0x69e8, 0x0abf, 0x441e, 0xa420, 0x396c, 0xe7c9, 0xa464);
//   scalar = -538;
//   VLOAD_8(v0, 0xAA, 0xAA);
//   VCLEAR(v1);
//   asm volatile("vrem.vx v1, v2, %[A], v0.t" ::[A] "r"(scalar));
//   VCMP_I16(14, v1, 0, 0xfe9d, 0, 0x00f4, 0, 0xff5c, 0, 0x0218, 0, 0x00d4, 0,
//            0x00de, 0, 0x00ae, 0, 0xfec2);

//   VSET(16, e32, m1);
//   VLOAD_32(v2, 0xf937dbf9, 0x6d855b59, 0x3bd09126, 0xaed11886, 0x6eb6f4bd,
//            0x5c639253, 0xca0f2abf, 0x57fec97b, 0x39496099, 0x8bfcdd58,
//            0x0f19f6e2, 0x2070c8d4, 0x8c689324, 0x2eecd9d7, 0xe2907e94,
//            0xb6cc2d44);
//   scalar = 649;
//   VLOAD_8(v0, 0xAA, 0xAA);
//   VCLEAR(v1);
//   asm volatile("vrem.vx v1, v2, %[A], v0.t" ::[A] "r"(scalar));
//   VCMP_I32(15, v1, 0, 0x00000116, 0, 0xffffffef, 0, 0x00000275, 0, 0x000000a9,
//            0, 0xfffffe09, 0, 0x0000023c, 0, 0x000000ce, 0, 0xfffffe0e);

//   VSET(16, e64, m1);
//   VLOAD_64(v2, 0x94236504e03e6525, 0x8d219d7afe5b2fb0, 0xc65a0b252860ab73,
//            0x2ca68636bacbc0bb, 0x275575f3e3fea940, 0x8f546251aaad354a,
//            0xb1462969035e0fa7, 0x5c9cdc19273ce111, 0x25a8487741ee75db,
//            0x38819f95e162663e, 0x698d19ce0e74ff8d, 0xb525257a9b5cd972,
//            0xb308a4fe0dcbb2f3, 0xf2fa735abc2db4d0, 0xc73c476461ac3f28,
//            0xb2830c2607bfffcc);
//   scalar = -59223;
//   VLOAD_8(v0, 0xAA, 0xAA);
//   VCLEAR(v1);
//   asm volatile("vrem.vx v1, v2, %[A], v0.t" ::[A] "r"(scalar));
//   VCMP_I64(16, v1, 0, 0xffffffffffff1f8a, 0, 0x000000000000cc8c, 0,
//            0xffffffffffffcecd, 0, 0x000000000000397b, 0, 0x0000000000006b00, 0,
//            0xffffffffffff9a21, 0, 0xffffffffffffca84, 0, 0xffffffffffff84dd);
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
