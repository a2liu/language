#include "pools.h"

#define BUCKET_SIZE 1024
#define DEFAULT_POOL_SIZE 1024
#define POOL_GROWTH_FACTOR 1.2

Pool::Pool(BucketArray *buckets, uint64_t size) noexcept {
  progress = begin = buckets->add(size);
  end = begin + size;
}

Pool::Pool() noexcept {
  progress = begin = new char[DEFAULT_POOL_SIZE];
  end = begin + DEFAULT_POOL_SIZE;
}
Pool::Pool(uint64_t size) noexcept {
  if (size < DEFAULT_POOL_SIZE) {
    size = DEFAULT_POOL_SIZE;
  }
  progress = begin = new char[size];
  end = begin + size;
}

char *Pool::add(uint64_t size) noexcept {
  if (size > end - progress) {
    return nullptr;
  }

  char *retLocation = progress;
  progress += size;
  return retLocation;
}

char *Pool::add_extend(BucketArray *buckets, uint64_t size) noexcept {
  if (size > end - progress) {
    uint64_t current_size = end - begin;
    uint64_t new_size = size + current_size * POOL_GROWTH_FACTOR;
    char *new_begin = buckets->add(new_size);
    memcpy(new_begin, begin, end - begin);
    progress = progress - begin + new_begin;
    end = new_begin + new_size;
    begin = new_begin;
  }

  char *retLocation = progress;
  progress += size;
  return retLocation;
}

BucketArray::Bucket Pool::push_to_buckets(BucketArray *buckets) noexcept {
  uint64_t size = progress - begin;
  char *bucket_begin = buckets->add(size);
  char *bucket_end = bucket_begin + size;
  memcpy(bucket_begin, begin, size);
  clear();
  return BucketArray::Bucket{bucket_begin, bucket_end};
}

void Pool::clear() noexcept { progress = begin; }

void Pool::free() noexcept {
  ::free(begin);
  begin = progress = end = nullptr;
}

void BucketArray::free() {
  for (auto bucket_ : buckets) {
    delete bucket_.begin;
  }
  buckets.clear();
}

char *BucketArray::add(uint64_t size) noexcept {
  size = (size - 1) / 16 * 16 + 16;
  if (buckets.size() == 0) {
    char *begin = new char[BUCKET_SIZE];
    buckets.push_back(Bucket{begin, begin});
  }

  if (size > BUCKET_SIZE) {
    Bucket old_back = buckets.back();
    char *begin = new char[size];
    buckets.back() = Bucket{begin, begin + size};
    buckets.push_back(old_back);
    return begin;
  }

  Bucket &last_bucket = buckets.back();
  if (BUCKET_SIZE - (last_bucket.progress - last_bucket.begin) < size) {
    char *begin = new char[BUCKET_SIZE];
    buckets.push_back(Bucket{begin, begin});
    last_bucket = buckets.back();
  }

  char *retLocation = last_bucket.progress;
  last_bucket.progress += size;
  return retLocation;
}
