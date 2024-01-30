#include <stdlib.h>
#include <string.h>
#include "privateFunctions.h"
#include "hashMapStruct.h"

//this may be replaced by a parameter, who knows?
#define DEFAULT_BUCKET_COUNT 17


hashMap* createHashMap(){
    hashMap* val = malloc(sizeof(hashMap) * DEFAULT_BUCKET_COUNT);
    val->bucketCount = DEFAULT_BUCKET_COUNT;
    val->elementCount = 0;
    val->buckets = malloc(sizeof(value) * val->bucketCount);
    return val;
}

value* lookUp(hashMap* hm, char* key){
    unsigned long hashValue = hash(key);
    unsigned long bucket = hashValue % hm->bucketCount;
    value* temp =  hm->buckets[bucket];
    if(temp == NULL){
        printf("key not found (no bucket)");
        return;
    } 
    else if(strcmp(temp->plainKey, key) == 0){
        return temp; 
    }
    while(strcmp(temp->plainKey, key) != 0){
        temp = temp->next;
    }
    if(temp->next == NULL){ 
        printf("key not found in bucket");
        return;
    }
    return temp;
}

void insert(hashMap* hm, char* key, void* val){
    unsigned long hashValue = hash(key);
    unsigned long bucket = hashValue % hm->bucketCount;
    value* temp =  hm->buckets[bucket];
    if(temp == NULL){
        hm->buckets[bucket] = malloc(sizeof(value));
        hm->buckets[bucket]->data = val;
        hm->buckets[bucket]->dataSize = sizeof(val);
        hm->buckets[bucket]->plainKey = key;
        hm->buckets[bucket]->next = NULL;
    }
    else{
        while(temp->next != NULL){
            temp = temp->next;
        };
        temp->next = malloc(sizeof(value));
        temp->next->data = val;
        temp->next->dataSize = sizeof(val);
        temp->next->plainKey = key;
        temp->next->next = NULL;
    }
}