#include "md5.h"

#define A 0x01234567
#define B 0x89abcdef
#define C 0xfedcba98
#define D 0x76543210

void md5__init(MD5_t*);
void md5__process(MD5_t*, uint8_t*, size_t);

uint8_t *md5__create_hash(char *input){
    MD5_t ctx;
    md5__init(&ctx);
}

void md5__init(MD5_t *ctx){
    ctx->size = (uint64_t) 0;
    ctx->buffer[0] = (uint32_t) A;
    ctx->buffer[1] = (uint32_t) B;
    ctx->buffer[2] = (uint32_t) C;
    ctx->buffer[3] = (uint32_t) D;
}

void md5__process(MD5_t *ctx, uint8_t *input, size_t input_len){

}