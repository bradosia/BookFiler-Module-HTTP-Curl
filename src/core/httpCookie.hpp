//
// CookieImpl.h
//
// Library: Net
// Package: HTTP
// Module:  CookieImpl
//
// Definition of the CookieImpl class.
//
// Copyright (c) 2005-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//

#ifndef BOOKFILER_MODULE_HTTP_HTTP_COOKIE_H
#define BOOKFILER_MODULE_HTTP_HTTP_COOKIE_H

// C++17
#include <string>
#include <unordered_map>
#include <chrono>
#include <sstream>
#include <iomanip>

// Local Project
#include "httpUtil.hpp"


/*
 * bookfiler - HTTP
 */
namespace bookfiler {
namespace HTTP {


class CookieImpl
	/// This class represents a HTTP Cookie.
	///
	/// A cookie is a small amount of information sent by a Web
	/// server to a Web browser, saved by the browser, and later sent back
	/// to the server. A cookie's value can uniquely identify a client, so
	/// cookies are commonly used for session management.
	///
	/// A cookie has a name, a single value, and optional attributes such
	/// as a comment, path and domain qualifiers, a maximum age, and a
	/// version number.
	///
	/// This class supports both the Version 0 (by Netscape) and Version 1
	/// (by RFC 2109) cookie specifications. By default, cookies are created
	/// using Version 0 to ensure the best interoperability.
{
public:
	enum SameSite
	{
		SAME_SITE_NOT_SPECIFIED,
		SAME_SITE_NONE,
		SAME_SITE_LAX,
		SAME_SITE_STRICT
	};

    CookieImpl();
        /// Creates an empty CookieImpl.

    explicit CookieImpl(const std::string& name);
		/// Creates a cookie with the given name.
		/// The cookie never expires.

    explicit CookieImpl(const std::unordered_map<std::string,std::string>& nvc);
        /// Creates a cookie from the given std::unordered_map<std::string,std::string>.

    CookieImpl(const std::string& name, const std::string& value);
		/// Creates a cookie with the given name and value.
		/// The cookie never expires.
		///
		/// Note: If value contains whitespace or non-alphanumeric
		/// characters, the value should be escaped by calling escape()
		/// before passing it to the constructor.

    CookieImpl(const CookieImpl& cookie);
        /// Creates the CookieImpl by copying another one.

    ~CookieImpl();
        /// Destroys the CookieImpl.

    CookieImpl& operator = (const CookieImpl& cookie);
		/// Assigns a cookie.

	void setVersion(int version);
		/// Sets the version of the cookie.
		///
		/// Version must be either 0 (denoting a Netscape cookie)
		/// or 1 (denoting a RFC 2109 cookie).

	int getVersion() const;
		/// Returns the version of the cookie, which is
		/// either 0 or 1.

	void setName(const std::string& name);
		/// Sets the name of the cookie.

	const std::string& getName() const;
		/// Returns the name of the cookie.

	void setValue(const std::string& value);
		/// Sets the value of the cookie.
		///
		/// According to the cookie specification, the
		/// size of the value should not exceed 4 Kbytes.
		///
		/// Note: If value contains whitespace or non-alphanumeric
		/// characters, the value should be escaped by calling escape()
		/// prior to passing it to setName().

	const std::string& getValue() const;
		/// Returns the value of the cookie.

	void setComment(const std::string& comment);
		/// Sets the comment for the cookie.
		///
		/// Comments are only supported for version 1 cookies.

	const std::string& getComment() const;
		/// Returns the comment for the cookie.

	void setDomain(const std::string& domain);
		/// Sets the domain for the cookie.

	const std::string& getDomain() const;
		/// Returns the domain for the cookie.

	void setPath(const std::string& path);
		/// Sets the path for the cookie.

	void setPriority(const std::string& priority);
		/// Sets the priority for the cookie.

	const std::string& getPath() const;
		/// Returns the path for the cookie.

	const std::string& getPriority() const;
		/// Returns the priority for the cookie.

	void setSecure(bool secure);
		/// Sets the value of the secure flag for
		/// the cookie.

	bool getSecure() const;
		/// Returns the value of the secure flag
		/// for the cookie.

	void setMaxAge(int maxAge);
		/// Sets the maximum age in seconds for
		/// the cookie.
		///
		/// A value of -1 (default) causes the cookie
		/// to become a session cookie, which will
		/// be deleted when the browser window
		/// is closed.
		///
		/// A value of 0 deletes the cookie on
		/// the client.

	int getMaxAge() const;
		/// Returns the maximum age in seconds for
		/// the cookie.

	void setHttpOnly(bool flag = true);
		/// Sets the HttpOnly flag for the cookie.

	bool getHttpOnly() const;
		/// Returns true iff the cookie's HttpOnly flag is set.

	void setSameSite(SameSite value);
		/// Sets the cookie's SameSite attribute.

	SameSite getSameSite() const;
		/// Returns the cookie's SameSite attribute.

	std::string toString() const;
		/// Returns a string representation of the cookie,
		/// suitable for use in a Set-Cookie header.

	static std::string escape(const std::string& str);
		/// Escapes the given string by replacing all
		/// non-alphanumeric characters with escape
		/// sequences in the form %xx, where xx is the
		/// hexadecimal character code.
		///
		/// The following characters will be replaced
		/// with escape sequences:
		///   - percent sign %
		///   - less-than and greater-than < and >
		///   - curly brackets { and }
		///   - square brackets [ and ]
		///   - parenthesis ( and )
		///   - solidus /
		///   - vertical line |
		///   - reverse solidus (backslash /)
		///   - quotation mark "
		///   - apostrophe '
		///   - circumflex accent ^
		///   - grave accent `
		///   - comma and semicolon , and ;
		///   - whitespace and control characters

	static std::string unescape(const std::string& str);
		/// Unescapes the given string by replacing all
		/// escape sequences in the form %xx with the
		/// respective characters.

private:
	int         _version;
	std::string _name;
	std::string _value;
	std::string _comment;
	std::string _domain;
	std::string _path;
	std::string _priority;
	bool        _secure;
	int         _maxAge;
	bool        _httpOnly;
	SameSite    _sameSite;
};


//
// inlines
//
inline int CookieImpl::getVersion() const
{
	return _version;
}


inline const std::string& CookieImpl::getName() const
{
	return _name;
}


inline const std::string& CookieImpl::getValue() const
{
	return _value;
}


inline const std::string& CookieImpl::getComment() const
{
	return _comment;
}


inline const std::string& CookieImpl::getDomain() const
{
	return _domain;
}


inline const std::string& CookieImpl::getPath() const
{
	return _path;
}


inline const std::string& CookieImpl::getPriority() const
{
	return _priority;
}


inline bool CookieImpl::getSecure() const
{
	return _secure;
}


inline int CookieImpl::getMaxAge() const
{
	return _maxAge;
}


inline bool CookieImpl::getHttpOnly() const
{
	return _httpOnly;
}


inline CookieImpl::SameSite CookieImpl::getSameSite() const
{
	return _sameSite;
}


} } // namespace Poco::Net


#endif // Net_CookieImpl_INCLUDED