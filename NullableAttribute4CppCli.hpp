#pragma once
#ifndef NULLABLE_ATTRIBUTE_FOR_CPPCLI_HPP
#define NULLABLE_ATTRIBUTE_FOR_CPPCLI_HPP

#if  defined(__cplusplus_cli)

// no-hint or forget: 0
#define DISALLOWNULL  1
#define ALLOWNULL     2
#define NOTNULL  ::System::Runtime::CompilerServices::\
    NullableAttribute(DISALLOWNULL)
#define NULLABLE ::System::Runtime::CompilerServices::\
    NullableAttribute(ALLOWNULL)

#define NOTNULL_CONTEXT  ::System::Runtime::CompilerServices::\
    NullableContextAttribute(DISALLOWNULL)
#define NULLABLE_CONTEXT ::System::Runtime::CompilerServices::\
    NullableContextAttribute(ALLOWNULL)

#define NULLABLE_ARRAY(...) ::System::Runtime::CompilerServices::\
    NullableAttribute(gcnew ::cli::array<::System::Byte, 1>{ __VA_ARGS__ })

#if !defined(_CLR_NETCORE)
// need backport to .NET Framework 4.x

namespace System {
namespace Runtime {
namespace CompilerServices {

[
    ::System::AttributeUsageAttribute(
        ::System::AttributeTargets::Class |
        ::System::AttributeTargets::Event |
        ::System::AttributeTargets::Field |
        ::System::AttributeTargets::GenericParameter |
        ::System::AttributeTargets::Module |
        ::System::AttributeTargets::Parameter |
        ::System::AttributeTargets::Property |
        ::System::AttributeTargets::ReturnValue |
        static_cast<::System::AttributeTargets>(0),
        AllowMultiple = false, Inherited = false)
]
/// <summary>
/// for nullable annotation.
/// see <seealso cref="https://github.com/dotnet/roslyn/blob/main/docs/features/nullable-metadata.md"/>.
/// </summary>
/// <remarks>
/// 0: oblivious, 1: notnull, 2: nullable.
/// </remarks>
ref class NullableAttribute sealed : ::System::Attribute {
public:
    ::cli::array<::System::Byte, 1>^ NullableFlags;
    NullableAttribute(::cli::array<::System::Byte, 1>^ flags)
        : NullableFlags(flags) { }
    NullableAttribute(::System::Byte flag)
        : NullableFlags(gcnew ::cli::array<::System::Byte, 1>(1)) {
        NullableFlags[0] = flag;
    }
    /// <summary>For Debug</summary>
    ::System::String^ ToString() override {
        return ::System::String::Join(", ", NullableFlags);
    }
};

[
    ::System::AttributeUsageAttribute(
        ::System::AttributeTargets::Class |
        ::System::AttributeTargets::Delegate |
        ::System::AttributeTargets::Interface |
        ::System::AttributeTargets::Method |
        ::System::AttributeTargets::Struct |
        static_cast<::System::AttributeTargets>(0),
        AllowMultiple = false, Inherited = false)
]
/// <summary>
/// for nullable annotation.
/// see <seealso cref="https://github.com/dotnet/roslyn/blob/main/docs/features/nullable-metadata.md"/>.
/// </summary>
/// <remarks>
/// 0: oblivious, 1: notnull, 2: nullable.
/// </remarks>
ref class NullableContextAttribute sealed : ::System::Attribute {
public:
    const ::System::Byte Flag;
    NullableContextAttribute(::System::Byte flag) : Flag(flag) { }
    /// <summary>For Debug</summary>
    ::System::String^ ToString() override {
        return ::System::String::Format("{0}", Flag);
    }
};

} // CompilerServices
} // Runtime
} // System

namespace System {
namespace Diagnostics {
namespace CodeAnalysis {
[
    ::System::AttributeUsageAttribute(
        ::System::AttributeTargets::Field |
        ::System::AttributeTargets::Parameter |
        ::System::AttributeTargets::Property |
        static_cast<::System::AttributeTargets>(0),
        Inherited = false)
]
ref class AllowNullAttribute sealed : ::System::Attribute {};
[
    ::System::AttributeUsageAttribute(
        ::System::AttributeTargets::Field |
        ::System::AttributeTargets::Parameter |
        ::System::AttributeTargets::Property |
        static_cast<::System::AttributeTargets>(0),
        Inherited = false)
]
ref class DisallowNullAttribute sealed : ::System::Attribute {};
[
    ::System::AttributeUsageAttribute(
        ::System::AttributeTargets::Field |
        ::System::AttributeTargets::Parameter |
        ::System::AttributeTargets::Property |
        ::System::AttributeTargets::ReturnValue |
        static_cast<::System::AttributeTargets>(0),
        Inherited = false)
]
ref class MaybeNullAttribute sealed : ::System::Attribute {};
[
    ::System::AttributeUsageAttribute(
        ::System::AttributeTargets::Field |
        ::System::AttributeTargets::Parameter |
        ::System::AttributeTargets::Property |
        ::System::AttributeTargets::ReturnValue |
        static_cast<::System::AttributeTargets>(0),
        Inherited = false)
]
ref class NotNullAttribute sealed : ::System::Attribute {};
[
    ::System::AttributeUsageAttribute(
        ::System::AttributeTargets::Parameter |
        static_cast<::System::AttributeTargets>(0),
        Inherited = false)
]
ref class MaybeNullWhenAttribute sealed : ::System::Attribute {
    bool const m_ReturnValue;
public:
    property bool ReturnValue {
        bool get() { return m_ReturnValue; }
    }
    MaybeNullWhenAttribute(bool returnValue)
        : m_ReturnValue(returnValue) { }
};
[
    ::System::AttributeUsageAttribute(
        ::System::AttributeTargets::Parameter |
        static_cast<::System::AttributeTargets>(0),
        Inherited = false)
]
ref class NotNullWhenAttribute sealed : ::System::Attribute {
    bool const m_ReturnValue;
public:
    property bool ReturnValue {
        bool get() { return m_ReturnValue; }
    }
    NotNullWhenAttribute(bool returnValue)
        : m_ReturnValue(returnValue) { }
};
[
    ::System::AttributeUsageAttribute(
        ::System::AttributeTargets::Parameter |
        ::System::AttributeTargets::Property |
        ::System::AttributeTargets::ReturnValue |
        static_cast<::System::AttributeTargets>(0),
        AllowMultiple = true, Inherited = false)
]
ref class NotNullIfNotNullAttribute sealed : ::System::Attribute {
    ::System::String^ const m_ParameterName;
public:
    property ::System::String^ ParameterName {
        ::System::String^ get() { return m_ParameterName; }
    }
    NotNullIfNotNullAttribute(::System::String^ parameterName)
        : m_ParameterName(parameterName) { }
};
[
    ::System::AttributeUsageAttribute(
        ::System::AttributeTargets::Method |
        static_cast<::System::AttributeTargets>(0),
        AllowMultiple = true, Inherited = false)
]
ref class DoesNotReturnAttribute sealed : ::System::Attribute {};
[
    ::System::AttributeUsageAttribute(
        ::System::AttributeTargets::Parameter |
        static_cast<::System::AttributeTargets>(0),
        AllowMultiple = true, Inherited = false)
]
ref class DoesNotReturnIfAttribute sealed : ::System::Attribute {
    bool const m_ParameterValue;
public:
    property bool ParameterValue {
        bool get() { return m_ParameterValue; }
    }
    DoesNotReturnIfAttribute(bool parameterValue)
        : m_ParameterValue(parameterValue) {}
};

// .NET 5
[
    ::System::AttributeUsageAttribute(
        ::System::AttributeTargets::Method |
        ::System::AttributeTargets::Property |
        static_cast<::System::AttributeTargets>(0),
        AllowMultiple = true, Inherited = false)
]
ref class MemberNotNullAttribute sealed : ::System::Attribute {
    ::cli::array<::System::String^>^ const m_Members;
public:
    property ::cli::array<::System::String^>^ Members {
        ::cli::array<::System::String^>^ get() { return m_Members; }
    }
    MemberNotNullAttribute(::cli::array<::System::String^>^ members)
        : m_Members(members) { }
    MemberNotNullAttribute(::System::String^ member)
        : m_Members(gcnew ::cli::array<::System::String^, 1>(1)) {
        m_Members[0] = member;
    }
};
[
    ::System::AttributeUsageAttribute(
        ::System::AttributeTargets::Method |
        ::System::AttributeTargets::Property |
        static_cast<::System::AttributeTargets>(0),
        AllowMultiple = true, Inherited = false)
]
ref class MemberNotNullWhenAttribute sealed : ::System::Attribute {
    bool const m_ReturnValue;
    ::cli::array<::System::String^>^ const m_Members;
public:
    property bool ReturnValue {
        bool get() { return m_ReturnValue; }
    }
    property ::cli::array<::System::String^>^ Members {
        ::cli::array<::System::String^>^ get() { return m_Members; }
    }
    MemberNotNullWhenAttribute(bool returnValue,
        ::cli::array<::System::String^>^ members)
        : m_ReturnValue(returnValue),
        m_Members(members) { }
    MemberNotNullWhenAttribute(bool returnValue,
        ::System::String^ member)
        : m_ReturnValue(returnValue),
        m_Members(gcnew ::cli::array<::System::String^, 1>(1)) {
        m_Members[0] = member;
    }
};


} // CodeAnalysis
} // Diagnostics
} // System

#endif// !defined(_CLR_NETCORE)
#endif//  defined(__cplusplus_cli)
#endif//NULLABLE_ATTRIBUTE_FOR_CPPCLI_HPP
