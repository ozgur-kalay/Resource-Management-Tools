#pragma once

// This Describes the bytes reserved for the meta data.

// PACK HEADER
#define META_BEG 0 //bytes
#define SIGNATURE_META_LEN 8 //bytes
#define RESOURCE_COUNT_META_LEN 4 //bytes


#define RESOURCE_COUNT_START 8
#define RESOURCE_TABLE_START 12 //bytes

// RESOURCE TABLE
// Resource Entry
#define ACCESS_NAME_META_LEN 2 //bytes
// ACCESS NAME: VARIABLE LENGTH
#define RESOURCE_TYPE_META_LEN 1 //bytes
#define DATA_OFFSET_META_LEN 8 //bytes
#define DATA_SIZE_META_LEN 8 //bytes