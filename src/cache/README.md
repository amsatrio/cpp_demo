# cache

## create proto object
```proto
syntax = "proto3";

enum CacheType {
  STRING = 0;
  INTEGER = 1;
}

message CacheObject {
  CacheType type = 1;
  string data = 2;
  int64 expired_at = 3;
}
```

## run this command to generate c++ files for the object

```bash
protoc --cpp_out=. cache.proto
```