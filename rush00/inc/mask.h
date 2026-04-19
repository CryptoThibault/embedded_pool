#ifndef MASK_H
#define MASK_H

#define MASK_1(A) (1 << (A))
#define MASK_2(A, B) MASK_1(B) | MASK_1(A)
#define MASK_3(A, B, C) MASK_1(C) | MASK_2(A, B)
#define MASK_4(A, B, C, D) MASK_1(D) | MASK_3(A, B, C)
#define MASK_5(A, B, C, D, E) MASK_1(E) | MASK_4(A, B, C, D)
#define MASK_6(A, B, C, D, E, F) MASK_1(F) | MASK_5(A, B, C, D, E)
#define MASK_7(A, B, C, D, E, F, G) MASK_1(G) | MASK_6(A, B, C, D, E, F)
#define MASK_8(A, B, C, D, E, F, G, H) MASK_1(H) | MASK_7(A, B, C, D, E, F, G)
#define GET_MASK(_1, _2, _3, _4, _5, _6, _7, _8, NAME, ...) NAME

#define MASK(...)	(GET_MASK(__VA_ARGS__, MASK_8, MASK_7, MASK_6, MASK_5, MASK_4, MASK_3, MASK_2, MASK_1)(__VA_ARGS__))

#endif
