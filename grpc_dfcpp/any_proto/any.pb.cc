// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: any.proto

#include "any.pb.h"

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
namespace any {
template <typename>
PROTOBUF_CONSTEXPR request::request(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_._has_bits_)*/{}
  , /*decltype(_impl_._cached_size_)*/{}
  , /*decltype(_impl_.data_)*/nullptr} {}
struct requestDefaultTypeInternal {
  PROTOBUF_CONSTEXPR requestDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~requestDefaultTypeInternal() {}
  union {
    request _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 requestDefaultTypeInternal _request_default_instance_;
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
template <typename>
PROTOBUF_CONSTEXPR person::person(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.name_)*/ {
    &::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized {}
  }

  , /*decltype(_impl_._cached_size_)*/{}} {}
struct personDefaultTypeInternal {
  PROTOBUF_CONSTEXPR personDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~personDefaultTypeInternal() {}
  union {
    person _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 personDefaultTypeInternal _person_default_instance_;
}  // namespace any
static ::_pb::Metadata file_level_metadata_any_2eproto[3];
static constexpr const ::_pb::EnumDescriptor**
    file_level_enum_descriptors_any_2eproto = nullptr;
static constexpr const ::_pb::ServiceDescriptor**
    file_level_service_descriptors_any_2eproto = nullptr;
const ::uint32_t TableStruct_any_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(
    protodesc_cold) = {
    PROTOBUF_FIELD_OFFSET(::any::request, _impl_._has_bits_),
    PROTOBUF_FIELD_OFFSET(::any::request, _internal_metadata_),
    ~0u,  // no _extensions_
    ~0u,  // no _oneof_case_
    ~0u,  // no _weak_field_map_
    ~0u,  // no _inlined_string_donated_
    ~0u,  // no _split_
    ~0u,  // no sizeof(Split)
    PROTOBUF_FIELD_OFFSET(::any::request, _impl_.data_),
    0,
    ~0u,  // no _has_bits_
    PROTOBUF_FIELD_OFFSET(::any::reply, _internal_metadata_),
    ~0u,  // no _extensions_
    ~0u,  // no _oneof_case_
    ~0u,  // no _weak_field_map_
    ~0u,  // no _inlined_string_donated_
    ~0u,  // no _split_
    ~0u,  // no sizeof(Split)
    PROTOBUF_FIELD_OFFSET(::any::reply, _impl_.ret_),
    ~0u,  // no _has_bits_
    PROTOBUF_FIELD_OFFSET(::any::person, _internal_metadata_),
    ~0u,  // no _extensions_
    ~0u,  // no _oneof_case_
    ~0u,  // no _weak_field_map_
    ~0u,  // no _inlined_string_donated_
    ~0u,  // no _split_
    ~0u,  // no sizeof(Split)
    PROTOBUF_FIELD_OFFSET(::any::person, _impl_.name_),
};

static const ::_pbi::MigrationSchema
    schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
        { 0, 9, -1, sizeof(::any::request)},
        { 10, -1, -1, sizeof(::any::reply)},
        { 19, -1, -1, sizeof(::any::person)},
};

static const ::_pb::Message* const file_default_instances[] = {
    &::any::_request_default_instance_._instance,
    &::any::_reply_default_instance_._instance,
    &::any::_person_default_instance_._instance,
};
const char descriptor_table_protodef_any_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
    "\n\tany.proto\022\003any\032\031google/protobuf/any.pr"
    "oto\"-\n\007request\022\"\n\004data\030\001 \001(\0132\024.google.pr"
    "otobuf.Any\"\024\n\005reply\022\013\n\003ret\030\001 \001(\005\"\026\n\006pers"
    "on\022\014\n\004name\030\001 \001(\t2-\n\003Any\022&\n\010send_any\022\014.an"
    "y.request\032\n.any.reply\"\000b\006proto3"
};
static const ::_pbi::DescriptorTable* const descriptor_table_any_2eproto_deps[1] =
    {
        &::descriptor_table_google_2fprotobuf_2fany_2eproto,
};
static ::absl::once_flag descriptor_table_any_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_any_2eproto = {
    false,
    false,
    191,
    descriptor_table_protodef_any_2eproto,
    "any.proto",
    &descriptor_table_any_2eproto_once,
    descriptor_table_any_2eproto_deps,
    1,
    3,
    schemas,
    file_default_instances,
    TableStruct_any_2eproto::offsets,
    file_level_metadata_any_2eproto,
    file_level_enum_descriptors_any_2eproto,
    file_level_service_descriptors_any_2eproto,
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
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_any_2eproto_getter() {
  return &descriptor_table_any_2eproto;
}
// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2
static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_any_2eproto(&descriptor_table_any_2eproto);
namespace any {
// ===================================================================

class request::_Internal {
 public:
  using HasBits = decltype(std::declval<request>()._impl_._has_bits_);
  static constexpr ::int32_t kHasBitsOffset =
    8 * PROTOBUF_FIELD_OFFSET(request, _impl_._has_bits_);
  static const ::PROTOBUF_NAMESPACE_ID::Any& data(const request* msg);
  static void set_has_data(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
};

const ::PROTOBUF_NAMESPACE_ID::Any&
request::_Internal::data(const request* msg) {
  return *msg->_impl_.data_;
}
void request::clear_data() {
  if (_impl_.data_ != nullptr) _impl_.data_->Clear();
  _impl_._has_bits_[0] &= ~0x00000001u;
}
request::request(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:any.request)
}
request::request(const request& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  request* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_._has_bits_){from._impl_._has_bits_}
    , /*decltype(_impl_._cached_size_)*/{}
    , decltype(_impl_.data_){nullptr}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  if ((from._impl_._has_bits_[0] & 0x00000001u) != 0) {
    _this->_impl_.data_ = new ::PROTOBUF_NAMESPACE_ID::Any(*from._impl_.data_);
  }
  // @@protoc_insertion_point(copy_constructor:any.request)
}

inline void request::SharedCtor(::_pb::Arena* arena) {
  (void)arena;
  new (&_impl_) Impl_{
      decltype(_impl_._has_bits_){}
    , /*decltype(_impl_._cached_size_)*/{}
    , decltype(_impl_.data_){nullptr}
  };
}

request::~request() {
  // @@protoc_insertion_point(destructor:any.request)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void request::SharedDtor() {
  ABSL_DCHECK(GetArenaForAllocation() == nullptr);
  if (this != internal_default_instance()) delete _impl_.data_;
}

void request::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void request::Clear() {
// @@protoc_insertion_point(message_clear_start:any.request)
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _impl_._has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    ABSL_DCHECK(_impl_.data_ != nullptr);
    _impl_.data_->Clear();
  }
  _impl_._has_bits_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* request::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    ::uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // .google.protobuf.Any data = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::uint8_t>(tag) == 10)) {
          ptr = ctx->ParseMessage(_internal_mutable_data(), ptr);
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
  _impl_._has_bits_.Or(has_bits);
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

::uint8_t* request::_InternalSerialize(
    ::uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:any.request)
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _impl_._has_bits_[0];
  // .google.protobuf.Any data = 1;
  if (cached_has_bits & 0x00000001u) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(1, _Internal::data(this),
        _Internal::data(this).GetCachedSize(), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:any.request)
  return target;
}

::size_t request::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:any.request)
  ::size_t total_size = 0;

  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // .google.protobuf.Any data = 1;
  cached_has_bits = _impl_._has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
        *_impl_.data_);
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData request::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    request::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*request::GetClassData() const { return &_class_data_; }


void request::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<request*>(&to_msg);
  auto& from = static_cast<const request&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:any.request)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if ((from._impl_._has_bits_[0] & 0x00000001u) != 0) {
    _this->_internal_mutable_data()->::PROTOBUF_NAMESPACE_ID::Any::MergeFrom(
        from._internal_data());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void request::CopyFrom(const request& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:any.request)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool request::IsInitialized() const {
  return true;
}

void request::InternalSwap(request* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_impl_._has_bits_[0], other->_impl_._has_bits_[0]);
  swap(_impl_.data_, other->_impl_.data_);
}

::PROTOBUF_NAMESPACE_ID::Metadata request::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_any_2eproto_getter, &descriptor_table_any_2eproto_once,
      file_level_metadata_any_2eproto[0]);
}
// ===================================================================

class reply::_Internal {
 public:
};

reply::reply(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:any.reply)
}
reply::reply(const reply& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(), _impl_(from._impl_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(
      from._internal_metadata_);
  // @@protoc_insertion_point(copy_constructor:any.reply)
}

inline void reply::SharedCtor(::_pb::Arena* arena) {
  (void)arena;
  new (&_impl_) Impl_{
      decltype(_impl_.ret_) { 0 }

    , /*decltype(_impl_._cached_size_)*/{}
  };
}

reply::~reply() {
  // @@protoc_insertion_point(destructor:any.reply)
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
// @@protoc_insertion_point(message_clear_start:any.reply)
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
  // @@protoc_insertion_point(serialize_to_array_start:any.reply)
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
  // @@protoc_insertion_point(serialize_to_array_end:any.reply)
  return target;
}

::size_t reply::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:any.reply)
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
  // @@protoc_insertion_point(class_specific_merge_from_start:any.reply)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_ret() != 0) {
    _this->_internal_set_ret(from._internal_ret());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void reply::CopyFrom(const reply& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:any.reply)
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
      &descriptor_table_any_2eproto_getter, &descriptor_table_any_2eproto_once,
      file_level_metadata_any_2eproto[1]);
}
// ===================================================================

class person::_Internal {
 public:
};

person::person(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:any.person)
}
person::person(const person& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  person* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.name_) {}

    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.name_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        _impl_.name_.Set("", GetArenaForAllocation());
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_name().empty()) {
    _this->_impl_.name_.Set(from._internal_name(), _this->GetArenaForAllocation());
  }
  // @@protoc_insertion_point(copy_constructor:any.person)
}

inline void person::SharedCtor(::_pb::Arena* arena) {
  (void)arena;
  new (&_impl_) Impl_{
      decltype(_impl_.name_) {}

    , /*decltype(_impl_._cached_size_)*/{}
  };
  _impl_.name_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        _impl_.name_.Set("", GetArenaForAllocation());
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

person::~person() {
  // @@protoc_insertion_point(destructor:any.person)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void person::SharedDtor() {
  ABSL_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.name_.Destroy();
}

void person::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void person::Clear() {
// @@protoc_insertion_point(message_clear_start:any.person)
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.name_.ClearToEmpty();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* person::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // string name = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::uint8_t>(tag) == 10)) {
          auto str = _internal_mutable_name();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "any.person.name"));
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

::uint8_t* person::_InternalSerialize(
    ::uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:any.person)
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // string name = 1;
  if (!this->_internal_name().empty()) {
    const std::string& _s = this->_internal_name();
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
        _s.data(), static_cast<int>(_s.length()), ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE, "any.person.name");
    target = stream->WriteStringMaybeAliased(1, _s, target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:any.person)
  return target;
}

::size_t person::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:any.person)
  ::size_t total_size = 0;

  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string name = 1;
  if (!this->_internal_name().empty()) {
    total_size += 1 + ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
                                    this->_internal_name());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData person::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    person::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*person::GetClassData() const { return &_class_data_; }


void person::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<person*>(&to_msg);
  auto& from = static_cast<const person&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:any.person)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_name().empty()) {
    _this->_internal_set_name(from._internal_name());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void person::CopyFrom(const person& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:any.person)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool person::IsInitialized() const {
  return true;
}

void person::InternalSwap(person* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.name_, lhs_arena,
                                       &other->_impl_.name_, rhs_arena);
}

::PROTOBUF_NAMESPACE_ID::Metadata person::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_any_2eproto_getter, &descriptor_table_any_2eproto_once,
      file_level_metadata_any_2eproto[2]);
}
// @@protoc_insertion_point(namespace_scope)
}  // namespace any
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::any::request*
Arena::CreateMaybeMessage< ::any::request >(Arena* arena) {
  return Arena::CreateMessageInternal< ::any::request >(arena);
}
template<> PROTOBUF_NOINLINE ::any::reply*
Arena::CreateMaybeMessage< ::any::reply >(Arena* arena) {
  return Arena::CreateMessageInternal< ::any::reply >(arena);
}
template<> PROTOBUF_NOINLINE ::any::person*
Arena::CreateMaybeMessage< ::any::person >(Arena* arena) {
  return Arena::CreateMessageInternal< ::any::person >(arena);
}
PROTOBUF_NAMESPACE_CLOSE
// @@protoc_insertion_point(global_scope)
#include "google/protobuf/port_undef.inc"
