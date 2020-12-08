// Code generated by protoc-gen-go. DO NOT EDIT.
// source: addressbook.proto

package tutorial

import (
	fmt "fmt"
	proto "github.com/golang/protobuf/proto"
	timestamp "github.com/golang/protobuf/ptypes/timestamp"
	math "math"
)

// Reference imports to suppress errors if they are not otherwise used.
var _ = proto.Marshal
var _ = fmt.Errorf
var _ = math.Inf

// This is a compile-time assertion to ensure that this generated file
// is compatible with the proto package it is being compiled against.
// A compilation error at this line likely means your copy of the
// proto package needs to be updated.
const _ = proto.ProtoPackageIsVersion3 // please upgrade the proto package

type Person_PhoneType int32

const (
	Person_MOBILE Person_PhoneType = 0
	Person_HOME   Person_PhoneType = 1
	Person_WORK   Person_PhoneType = 2
)

var Person_PhoneType_name = map[int32]string{
	0: "MOBILE",
	1: "HOME",
	2: "WORK",
}

var Person_PhoneType_value = map[string]int32{
	"MOBILE": 0,
	"HOME":   1,
	"WORK":   2,
}

func (x Person_PhoneType) String() string {
	return proto.EnumName(Person_PhoneType_name, int32(x))
}

func (Person_PhoneType) EnumDescriptor() ([]byte, []int) {
	return fileDescriptor_1eb1a68c9dd6d429, []int{0, 0}
}

type Person struct {
	Name                 string                `protobuf:"bytes,1,opt,name=name,proto3" json:"name,omitempty"`
	Id                   int32                 `protobuf:"varint,2,opt,name=id,proto3" json:"id,omitempty"`
	Email                string                `protobuf:"bytes,3,opt,name=email,proto3" json:"email,omitempty"`
	Phones               []*Person_PhoneNumber `protobuf:"bytes,4,rep,name=phones,proto3" json:"phones,omitempty"`
	LastUpdated          *timestamp.Timestamp  `protobuf:"bytes,5,opt,name=last_updated,json=lastUpdated,proto3" json:"last_updated,omitempty"`
	XXX_NoUnkeyedLiteral struct{}              `json:"-"`
	XXX_unrecognized     []byte                `json:"-"`
	XXX_sizecache        int32                 `json:"-"`
}

func (m *Person) Reset()         { *m = Person{} }
func (m *Person) String() string { return proto.CompactTextString(m) }
func (*Person) ProtoMessage()    {}
func (*Person) Descriptor() ([]byte, []int) {
	return fileDescriptor_1eb1a68c9dd6d429, []int{0}
}

func (m *Person) XXX_Unmarshal(b []byte) error {
	return xxx_messageInfo_Person.Unmarshal(m, b)
}
func (m *Person) XXX_Marshal(b []byte, deterministic bool) ([]byte, error) {
	return xxx_messageInfo_Person.Marshal(b, m, deterministic)
}
func (m *Person) XXX_Merge(src proto.Message) {
	xxx_messageInfo_Person.Merge(m, src)
}
func (m *Person) XXX_Size() int {
	return xxx_messageInfo_Person.Size(m)
}
func (m *Person) XXX_DiscardUnknown() {
	xxx_messageInfo_Person.DiscardUnknown(m)
}

var xxx_messageInfo_Person proto.InternalMessageInfo

func (m *Person) GetName() string {
	if m != nil {
		return m.Name
	}
	return ""
}

func (m *Person) GetId() int32 {
	if m != nil {
		return m.Id
	}
	return 0
}

func (m *Person) GetEmail() string {
	if m != nil {
		return m.Email
	}
	return ""
}

func (m *Person) GetPhones() []*Person_PhoneNumber {
	if m != nil {
		return m.Phones
	}
	return nil
}

func (m *Person) GetLastUpdated() *timestamp.Timestamp {
	if m != nil {
		return m.LastUpdated
	}
	return nil
}

type Person_PhoneNumber struct {
	Number               string           `protobuf:"bytes,1,opt,name=number,proto3" json:"number,omitempty"`
	Type                 Person_PhoneType `protobuf:"varint,2,opt,name=type,proto3,enum=tutorial.Person_PhoneType" json:"type,omitempty"`
	XXX_NoUnkeyedLiteral struct{}         `json:"-"`
	XXX_unrecognized     []byte           `json:"-"`
	XXX_sizecache        int32            `json:"-"`
}

func (m *Person_PhoneNumber) Reset()         { *m = Person_PhoneNumber{} }
func (m *Person_PhoneNumber) String() string { return proto.CompactTextString(m) }
func (*Person_PhoneNumber) ProtoMessage()    {}
func (*Person_PhoneNumber) Descriptor() ([]byte, []int) {
	return fileDescriptor_1eb1a68c9dd6d429, []int{0, 0}
}

func (m *Person_PhoneNumber) XXX_Unmarshal(b []byte) error {
	return xxx_messageInfo_Person_PhoneNumber.Unmarshal(m, b)
}
func (m *Person_PhoneNumber) XXX_Marshal(b []byte, deterministic bool) ([]byte, error) {
	return xxx_messageInfo_Person_PhoneNumber.Marshal(b, m, deterministic)
}
func (m *Person_PhoneNumber) XXX_Merge(src proto.Message) {
	xxx_messageInfo_Person_PhoneNumber.Merge(m, src)
}
func (m *Person_PhoneNumber) XXX_Size() int {
	return xxx_messageInfo_Person_PhoneNumber.Size(m)
}
func (m *Person_PhoneNumber) XXX_DiscardUnknown() {
	xxx_messageInfo_Person_PhoneNumber.DiscardUnknown(m)
}

var xxx_messageInfo_Person_PhoneNumber proto.InternalMessageInfo

func (m *Person_PhoneNumber) GetNumber() string {
	if m != nil {
		return m.Number
	}
	return ""
}

func (m *Person_PhoneNumber) GetType() Person_PhoneType {
	if m != nil {
		return m.Type
	}
	return Person_MOBILE
}

type Person_AddressBook struct {
	People               []*Person `protobuf:"bytes,1,rep,name=people,proto3" json:"people,omitempty"`
	XXX_NoUnkeyedLiteral struct{}  `json:"-"`
	XXX_unrecognized     []byte    `json:"-"`
	XXX_sizecache        int32     `json:"-"`
}

func (m *Person_AddressBook) Reset()         { *m = Person_AddressBook{} }
func (m *Person_AddressBook) String() string { return proto.CompactTextString(m) }
func (*Person_AddressBook) ProtoMessage()    {}
func (*Person_AddressBook) Descriptor() ([]byte, []int) {
	return fileDescriptor_1eb1a68c9dd6d429, []int{0, 1}
}

func (m *Person_AddressBook) XXX_Unmarshal(b []byte) error {
	return xxx_messageInfo_Person_AddressBook.Unmarshal(m, b)
}
func (m *Person_AddressBook) XXX_Marshal(b []byte, deterministic bool) ([]byte, error) {
	return xxx_messageInfo_Person_AddressBook.Marshal(b, m, deterministic)
}
func (m *Person_AddressBook) XXX_Merge(src proto.Message) {
	xxx_messageInfo_Person_AddressBook.Merge(m, src)
}
func (m *Person_AddressBook) XXX_Size() int {
	return xxx_messageInfo_Person_AddressBook.Size(m)
}
func (m *Person_AddressBook) XXX_DiscardUnknown() {
	xxx_messageInfo_Person_AddressBook.DiscardUnknown(m)
}

var xxx_messageInfo_Person_AddressBook proto.InternalMessageInfo

func (m *Person_AddressBook) GetPeople() []*Person {
	if m != nil {
		return m.People
	}
	return nil
}

func init() {
	proto.RegisterEnum("tutorial.Person_PhoneType", Person_PhoneType_name, Person_PhoneType_value)
	proto.RegisterType((*Person)(nil), "tutorial.Person")
	proto.RegisterType((*Person_PhoneNumber)(nil), "tutorial.Person.PhoneNumber")
	proto.RegisterType((*Person_AddressBook)(nil), "tutorial.Person.AddressBook")
}

func init() { proto.RegisterFile("addressbook.proto", fileDescriptor_1eb1a68c9dd6d429) }

var fileDescriptor_1eb1a68c9dd6d429 = []byte{
	// 310 bytes of a gzipped FileDescriptorProto
	0x1f, 0x8b, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0xff, 0x6c, 0x90, 0x41, 0x4b, 0xc3, 0x30,
	0x14, 0xc7, 0x6d, 0xd7, 0x95, 0xed, 0x55, 0x46, 0x0d, 0x22, 0xa5, 0x08, 0x96, 0x9d, 0x0a, 0x42,
	0x06, 0x53, 0xf0, 0xe4, 0xc1, 0xc1, 0x40, 0xd1, 0xb9, 0x11, 0x36, 0x3c, 0x4a, 0x4a, 0xe3, 0x2c,
	0x6b, 0xfb, 0x42, 0x9b, 0x1e, 0xf6, 0xbd, 0xfd, 0x00, 0xd2, 0xa4, 0x15, 0x11, 0x6f, 0x2f, 0x79,
	0x3f, 0xfe, 0xfc, 0xfe, 0x0f, 0xce, 0x78, 0x9a, 0x56, 0xa2, 0xae, 0x13, 0xc4, 0x03, 0x95, 0x15,
	0x2a, 0x24, 0x23, 0xd5, 0x28, 0xac, 0x32, 0x9e, 0x87, 0x57, 0x7b, 0xc4, 0x7d, 0x2e, 0x66, 0xfa,
	0x3f, 0x69, 0x3e, 0x66, 0x2a, 0x2b, 0x44, 0xad, 0x78, 0x21, 0x0d, 0x3a, 0xfd, 0xb2, 0xc1, 0xdd,
	0x88, 0xaa, 0xc6, 0x92, 0x10, 0x70, 0x4a, 0x5e, 0x88, 0xc0, 0x8a, 0xac, 0x78, 0xcc, 0xf4, 0x4c,
	0x26, 0x60, 0x67, 0x69, 0x60, 0x47, 0x56, 0x3c, 0x64, 0x76, 0x96, 0x92, 0x73, 0x18, 0x8a, 0x82,
	0x67, 0x79, 0x30, 0xd0, 0x90, 0x79, 0x90, 0x5b, 0x70, 0xe5, 0x27, 0x96, 0xa2, 0x0e, 0x9c, 0x68,
	0x10, 0x7b, 0xf3, 0x4b, 0xda, 0x0b, 0x50, 0x93, 0x4d, 0x37, 0xed, 0xfa, 0xb5, 0x29, 0x12, 0x51,
	0xb1, 0x8e, 0x25, 0xf7, 0x70, 0x9a, 0xf3, 0x5a, 0xbd, 0x37, 0x32, 0xe5, 0x4a, 0xa4, 0xc1, 0x30,
	0xb2, 0x62, 0x6f, 0x1e, 0x52, 0xa3, 0x4c, 0x7b, 0x65, 0xba, 0xed, 0x95, 0x99, 0xd7, 0xf2, 0x3b,
	0x83, 0x87, 0x3b, 0xf0, 0x7e, 0xa5, 0x92, 0x0b, 0x70, 0x4b, 0x3d, 0x75, 0xfe, 0xdd, 0x8b, 0x50,
	0x70, 0xd4, 0x51, 0x0a, 0xdd, 0x61, 0x32, 0x0f, 0xff, 0x37, 0xdb, 0x1e, 0xa5, 0x60, 0x9a, 0x0b,
	0xef, 0xc0, 0x7b, 0x30, 0x07, 0x5d, 0x20, 0x1e, 0x48, 0x0c, 0xae, 0x14, 0x28, 0xf3, 0xf6, 0x2c,
	0x6d, 0x35, 0xff, 0x6f, 0x00, 0xeb, 0xf6, 0xd3, 0x6b, 0x18, 0xff, 0x64, 0x11, 0x00, 0x77, 0xb5,
	0x5e, 0x3c, 0xbd, 0x2c, 0xfd, 0x13, 0x32, 0x02, 0xe7, 0x71, 0xbd, 0x5a, 0xfa, 0x56, 0x3b, 0xbd,
	0xad, 0xd9, 0xb3, 0x6f, 0x27, 0xae, 0x6e, 0x77, 0xf3, 0x1d, 0x00, 0x00, 0xff, 0xff, 0x39, 0x16,
	0xc0, 0xbf, 0xbd, 0x01, 0x00, 0x00,
}
