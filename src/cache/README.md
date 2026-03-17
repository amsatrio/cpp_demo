# cache

## create proto object
```proto
syntax = "proto3";

enum CacheType {
  STRING = 0;
  BINARY = 1;
}

message CacheObject {
  bytes blob_val = 1;
  CacheType type = 2;
  int64 expired_at = 3;
}
```

## run this command to generate c++ files for the object

```bash
protoc --cpp_out=. cache.proto
```