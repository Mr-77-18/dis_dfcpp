// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: commu.proto

#include "commu.pb.h"

#include <algorithm>
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/extension_set.h"
#include "google/protobuf/wire_format_lite.h"
#include "google/protobuf/descriptor.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/reflection_ops.h"
#include "google/protobuf/wire_format.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"
PROTOBUF_PRAGMA_INIT_SEG
namespace _pb = ::PROTOBUF_NAMESPACE_ID;
namespace _pbi = ::PROTOBUF_NAMESPACE_ID::internal;
namespace commu {
template <typename>
PROTOBUF_CONSTEXPR index::index(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_._index_)*/ {}
  ,/* _impl_.__index_cached_byte_size_ = */ { 0 }

  , /*decltype(_impl_._cached_size_)*/{}} {}
struct indexDefaultTypeInternal {
  PROTOBUF_CONSTEXPR indexDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~indexDefaultTypeInternal() {}
  union {
    index _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 indexDefaultTypeInternal _index_default_instance_;
template <typename>
PROTOBUF_CONSTEXPR reply::reply(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.ret_)*/ 0

  , /*decltype(_impl_._cached_size_)*/{}} {}
struct replyDefaultTypeInternal {
  PROTOBUF_CONSTEXPR replyDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~replyDefaultTypeInternal() {}
  union {
    reply _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 replyDefaultTypeInternal _reply_default_instance_;
}  // namespace commu
static ::_pb::Metadata file_level_metadata_commu_2eproto[2];
static constexpr const ::_pb::EnumDescriptor**
    file_level_enum_descriptors_commu_2eproto = nullptr;
static constexpr const ::_pb::ServiceDescriptor**
    file_level_service_descriptors_commu_2eproto = nullptr;
const ::uint32_t TableStruct_commu_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(
    protodesc_cold) = {
    ~0u,  // no _has_bits_
    PROTOBUF_FIELD_OFFSET(::commu::index, _internal_metadata_),
    ~0u,  // no _extensions_
    ~0u,  // no _oneof_case_
    ~0u,  // no _weak_field_map_
    ~0u,  // no _inlined_string_donated_
    ~0u,  // no _split_
    ~0u,  // no sizeof(Split)
    PROTOBUF_FIELD_OFFSET(::commu::index, _impl_._index_),
    ~0u,  // no _has_bits_
    PROTOBUF_FIELD_OFFSET(::commu::reply, _internal_metadata_),
    ~0u,  // no _extensions_
    ~0u,  // no _oneof_case_
    ~0u,  // no _weak_field_map_
    ~0u,  // no _inlined_string_donated_
    ~0u,  // no _split_
    ~0u,  // no sizeof(Split)
    PROTOBUF_FIELD_OFFSET(::commu::reply, _impl_.ret_),
};

static const ::_pbi::MigrationSchema
    schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
        { 0, -1, -1, sizeof(::commu::index)},
        { 9, -1, -1, sizeof(::commu::reply)},
};

static const ::_pb::Message* const file_default_instances[] = {
    &::commu::_index_default_instance_._instance,
    &::commu::_reply_default_instance_._instance,
};
const char descriptor_table_protodef_commu_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
    "\n\013commu.proto\022\005commu\"\027\n\005index\022\016\n\006_index\030"
    "\001 \003(\005\"\024\n\005reply\022\013\n\003ret\030\001 \001(\00523\n\005Commu\022*\n\n"
    "send_index\022\014.commu.index\032\014.commu.reply\"\000"
    "b\006proto3"
};
static ::absl::once_flag descriptor_table_commu_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_commu_2eproto = {
    false,
    false,
    128,
    descriptor_table_protodef_commu_2eproto,
    "commu.proto",
    &descriptor_table_commu_2eproto_once,
    nullptr,
    0,
    2,
    schemas,
    file_default_instances,
    TableStruct_commu_2eproto::offsets,
    file_level_metadata_commu_2eproto,
    file_level_enum_descriptors_commu_2eproto,
    file_level_service_descriptors_commu_2eproto,
};

// This function exists to be marked as weak.
// It can significantly speed up compilation by breaking up LLVM's SCC
// in the .pb.cc translation units. Large translation units see a
// reduction of more than 35% of walltime for optimized builds. Without
// the weak attribute all the messages in the file, including all the
// vtables and everything they use become part of the same SCC through
// a cycle like:
// GetMetadata -> descriptor table -> default instances ->
//   vtables -> GetMetadata
// By adding a weak function here we break the connection from the
// individual vtables back into the descriptor table.
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_commu_2eproto_getter() {
  return &descriptor_table_commu_2eproto;
}
// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2
static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_commu_2eproto(&descriptor_table_commu_2eproto);
namespace commu {
// ===================================================================

class index::_Internal {
 public:
};

index::index(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:commu.index)
}
index::index(const index& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  index* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_._index_) { from._impl_._index_ }
    ,/* _impl_.__index_cached_byte_size_ = */ { 0 }

    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  // @@protoc_insertion_point(copy_constructor:commu.index)
}

inline void index::SharedCtor(::_pb::Arena* arena) {
  (void)arena;
  new (&_impl_) Impl_{
      decltype(_impl_._index_) { arena }
    ,/* _impl_.__index_cached_byte_size_ = */ { 0 }

    , /*decltype(_impl_._cached_size_)*/{}
  };
}

index::~index() {
  // @@protoc_insertion_point(destructor:commu.index)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void index::SharedDtor() {
  ABSL_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_._index_.~RepeatedField();
}

void index::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void index::Clear() {
// @@protoc_insertion_point(message_clear_start:commu.index)
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _internal_mutable__index()->Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* index::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // repeated int32 _index = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::uint8_t>(tag) == 10)) {
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::PackedInt32Parser(_internal_mutable__index(), ptr, ctx);
          CHK_(ptr);
        } else if (static_cast<::uint8_t>(tag) == 8) {
          _internal_add__index(::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr));
          CHK_(ptr);
        } else {
          goto handle_unusual;
        }
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

::uint8_t* index::_InternalSerialize(
    ::uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:commu.index)
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated int32 _index = 1;
  {
    int byte_size = _impl_.__index_cached_byte_size_.Get();
    if (byte_size > 0) {
      target = stream->WriteInt32Packed(1, _internal__index(),
                                                 byte_size, target);
    }
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:commu.index)
  return target;
}

::size_t index::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:commu.index)
  ::size_t total_size = 0;

  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated int32 _index = 1;
  {
    std::size_t data_size = ::_pbi::WireFormatLite::Int32Size(
        this->_internal__index())
    ;
    _impl_.__index_cached_byte_size_.Set(::_pbi::ToCachedSize(data_size));
    std::size_t tag_size = data_size == 0
        ? 0
        : 1 + ::_pbi::WireFormatLite::Int32Size(
                            static_cast<int32_t>(data_size))
    ;
    total_size += tag_size + data_size;
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData index::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    index::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*index::GetClassData() const { return &_class_data_; }


void index::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<index*>(&to_msg);
  auto& from = static_cast<const index&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:commu.index)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  _this->_impl_._index_.MergeFrom(from._impl_._index_);
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void index::CopyFrom(const index& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:commu.index)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool index::IsInitialized() const {
  return true;
}

void index::InternalSwap(index* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  _impl_._index_.InternalSwap(&other->_impl_._index_);
}

::PROTOBUF_NAMESPACE_ID::Metadata index::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_commu_2eproto_getter, &descriptor_table_commu_2eproto_once,
      file_level_metadata_commu_2eproto[0]);
}
// ===================================================================

class reply::_Internal {
 public:
};

reply::reply(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:commu.reply)
}
reply::reply(const reply& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(), _impl_(from._impl_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(
      from._internal_metadata_);
  // @@protoc_insertion_point(copy_constructor:commu.reply)
}

inline void reply::SharedCtor(::_pb::Arena* arena) {
  (void)arena;
  new (&_impl_) Impl_{
      decltype(_impl_.ret_) { 0 }

    , /*decltype(_impl_._cached_size_)*/{}
  };
}

reply::~reply() {
  // @@protoc_insertion_point(destructor:commu.reply)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void reply::SharedDtor() {
  ABSL_DCHECK(GetArenaForAllocation() == nullptr);
}

void reply::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void reply::Clear() {
// @@protoc_insertion_point(message_clear_start:commu.reply)
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.ret_ = 0;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* reply::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // int32 ret = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::uint8_t>(tag) == 8)) {
          _impl_.ret_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else {
          goto handle_unusual;
        }
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

::uint8_t* reply::_InternalSerialize(
    ::uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:commu.reply)
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 ret = 1;
  if (this->_internal_ret() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(
        1, this->_internal_ret(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:commu.reply)
  return target;
}

::size_t reply::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:commu.reply)
  ::size_t total_size = 0;

  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // int32 ret = 1;
  if (this->_internal_ret() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(
        this->_internal_ret());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData reply::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    reply::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*reply::GetClassData() const { return &_class_data_; }


void reply::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<reply*>(&to_msg);
  auto& from = static_cast<const reply&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:commu.reply)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_ret() != 0) {
    _this->_internal_set_ret(from._internal_ret());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void reply::CopyFrom(const reply& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:commu.reply)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool reply::IsInitialized() const {
  return true;
}

void reply::InternalSwap(reply* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);

  swap(_impl_.ret_, other->_impl_.ret_);
}

::PROTOBUF_NAMESPACE_ID::Metadata reply::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_commu_2eproto_getter, &descriptor_table_commu_2eproto_once,
      file_level_metadata_commu_2eproto[1]);
}
// @@protoc_insertion_point(namespace_scope)
}  // namespace commu
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::commu::index*
Arena::CreateMaybeMessage< ::commu::index >(Arena* arena) {
  return Arena::CreateMessageInternal< ::commu::index >(arena);
}
template<> PROTOBUF_NOINLINE ::commu::reply*
Arena::CreateMaybeMessage< ::commu::reply >(Arena* arena) {
  return Arena::CreateMessageInternal< ::commu::reply >(arena);
}
PROTOBUF_NAMESPACE_CLOSE
// @@protoc_insertion_point(global_scope)
#include "google/protobuf/port_undef.inc"