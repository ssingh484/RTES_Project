/**
 * Autogenerated by Thrift Compiler (0.13.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef buzzblog_TYPES_H
#define buzzblog_TYPES_H

#include <iosfwd>

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/TBase.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>

#include <functional>
#include <memory>


namespace gen {

class TAccount;

class TFollow;

class TFollowQuery;

class TPost;

class TLike;

class TUniquepair;

class TUniquepairQuery;

class TAccountInvalidCredentialsException;

class TAccountDeactivatedException;

class TAccountInvalidAttributesException;

class TAccountUsernameAlreadyExistsException;

class TAccountNotFoundException;

class TAccountNotAuthorizedException;

class TFollowAlreadyExistsException;

class TFollowNotFoundException;

class TFollowNotAuthorizedException;

class TLikeAlreadyExistsException;

class TLikeNotFoundException;

class TLikeNotAuthorizedException;

class TPostInvalidAttributesException;

class TPostNotFoundException;

class TPostNotAuthorizedException;

class TUniquepairNotFoundException;

class TUniquepairAlreadyExistsException;

typedef struct _TAccount__isset {
  _TAccount__isset() : follows_you(false), followed_by_you(false), n_followers(false), n_following(false), n_posts(false), n_likes(false) {}
  bool follows_you :1;
  bool followed_by_you :1;
  bool n_followers :1;
  bool n_following :1;
  bool n_posts :1;
  bool n_likes :1;
} _TAccount__isset;

class TAccount : public virtual ::apache::thrift::TBase {
 public:

  TAccount(const TAccount&);
  TAccount& operator=(const TAccount&);
  TAccount() : id(0), created_at(0), active(0), username(), first_name(), last_name(), follows_you(0), followed_by_you(0), n_followers(0), n_following(0), n_posts(0), n_likes(0) {
  }

  virtual ~TAccount() noexcept;
  int32_t id;
  int32_t created_at;
  bool active;
  std::string username;
  std::string first_name;
  std::string last_name;
  bool follows_you;
  bool followed_by_you;
  int32_t n_followers;
  int32_t n_following;
  int32_t n_posts;
  int32_t n_likes;

  _TAccount__isset __isset;

  void __set_id(const int32_t val);

  void __set_created_at(const int32_t val);

  void __set_active(const bool val);

  void __set_username(const std::string& val);

  void __set_first_name(const std::string& val);

  void __set_last_name(const std::string& val);

  void __set_follows_you(const bool val);

  void __set_followed_by_you(const bool val);

  void __set_n_followers(const int32_t val);

  void __set_n_following(const int32_t val);

  void __set_n_posts(const int32_t val);

  void __set_n_likes(const int32_t val);

  bool operator == (const TAccount & rhs) const
  {
    if (!(id == rhs.id))
      return false;
    if (!(created_at == rhs.created_at))
      return false;
    if (!(active == rhs.active))
      return false;
    if (!(username == rhs.username))
      return false;
    if (!(first_name == rhs.first_name))
      return false;
    if (!(last_name == rhs.last_name))
      return false;
    if (__isset.follows_you != rhs.__isset.follows_you)
      return false;
    else if (__isset.follows_you && !(follows_you == rhs.follows_you))
      return false;
    if (__isset.followed_by_you != rhs.__isset.followed_by_you)
      return false;
    else if (__isset.followed_by_you && !(followed_by_you == rhs.followed_by_you))
      return false;
    if (__isset.n_followers != rhs.__isset.n_followers)
      return false;
    else if (__isset.n_followers && !(n_followers == rhs.n_followers))
      return false;
    if (__isset.n_following != rhs.__isset.n_following)
      return false;
    else if (__isset.n_following && !(n_following == rhs.n_following))
      return false;
    if (__isset.n_posts != rhs.__isset.n_posts)
      return false;
    else if (__isset.n_posts && !(n_posts == rhs.n_posts))
      return false;
    if (__isset.n_likes != rhs.__isset.n_likes)
      return false;
    else if (__isset.n_likes && !(n_likes == rhs.n_likes))
      return false;
    return true;
  }
  bool operator != (const TAccount &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TAccount & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(TAccount &a, TAccount &b);

std::ostream& operator<<(std::ostream& out, const TAccount& obj);

typedef struct _TFollow__isset {
  _TFollow__isset() : follower(false), followee(false) {}
  bool follower :1;
  bool followee :1;
} _TFollow__isset;

class TFollow : public virtual ::apache::thrift::TBase {
 public:

  TFollow(const TFollow&);
  TFollow& operator=(const TFollow&);
  TFollow() : id(0), created_at(0), follower_id(0), followee_id(0) {
  }

  virtual ~TFollow() noexcept;
  int32_t id;
  int32_t created_at;
  int32_t follower_id;
  int32_t followee_id;
  TAccount follower;
  TAccount followee;

  _TFollow__isset __isset;

  void __set_id(const int32_t val);

  void __set_created_at(const int32_t val);

  void __set_follower_id(const int32_t val);

  void __set_followee_id(const int32_t val);

  void __set_follower(const TAccount& val);

  void __set_followee(const TAccount& val);

  bool operator == (const TFollow & rhs) const
  {
    if (!(id == rhs.id))
      return false;
    if (!(created_at == rhs.created_at))
      return false;
    if (!(follower_id == rhs.follower_id))
      return false;
    if (!(followee_id == rhs.followee_id))
      return false;
    if (__isset.follower != rhs.__isset.follower)
      return false;
    else if (__isset.follower && !(follower == rhs.follower))
      return false;
    if (__isset.followee != rhs.__isset.followee)
      return false;
    else if (__isset.followee && !(followee == rhs.followee))
      return false;
    return true;
  }
  bool operator != (const TFollow &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TFollow & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(TFollow &a, TFollow &b);

std::ostream& operator<<(std::ostream& out, const TFollow& obj);

typedef struct _TFollowQuery__isset {
  _TFollowQuery__isset() : follower_id(false), followee_id(false) {}
  bool follower_id :1;
  bool followee_id :1;
} _TFollowQuery__isset;

class TFollowQuery : public virtual ::apache::thrift::TBase {
 public:

  TFollowQuery(const TFollowQuery&);
  TFollowQuery& operator=(const TFollowQuery&);
  TFollowQuery() : follower_id(0), followee_id(0) {
  }

  virtual ~TFollowQuery() noexcept;
  int32_t follower_id;
  int32_t followee_id;

  _TFollowQuery__isset __isset;

  void __set_follower_id(const int32_t val);

  void __set_followee_id(const int32_t val);

  bool operator == (const TFollowQuery & rhs) const
  {
    if (__isset.follower_id != rhs.__isset.follower_id)
      return false;
    else if (__isset.follower_id && !(follower_id == rhs.follower_id))
      return false;
    if (__isset.followee_id != rhs.__isset.followee_id)
      return false;
    else if (__isset.followee_id && !(followee_id == rhs.followee_id))
      return false;
    return true;
  }
  bool operator != (const TFollowQuery &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TFollowQuery & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(TFollowQuery &a, TFollowQuery &b);

std::ostream& operator<<(std::ostream& out, const TFollowQuery& obj);

typedef struct _TPost__isset {
  _TPost__isset() : author(false), n_likes(false) {}
  bool author :1;
  bool n_likes :1;
} _TPost__isset;

class TPost : public virtual ::apache::thrift::TBase {
 public:

  TPost(const TPost&);
  TPost& operator=(const TPost&);
  TPost() : id(0), created_at(0), active(0), text(), author_id(0), n_likes(0) {
  }

  virtual ~TPost() noexcept;
  int32_t id;
  int32_t created_at;
  bool active;
  std::string text;
  int32_t author_id;
  TAccount author;
  int32_t n_likes;

  _TPost__isset __isset;

  void __set_id(const int32_t val);

  void __set_created_at(const int32_t val);

  void __set_active(const bool val);

  void __set_text(const std::string& val);

  void __set_author_id(const int32_t val);

  void __set_author(const TAccount& val);

  void __set_n_likes(const int32_t val);

  bool operator == (const TPost & rhs) const
  {
    if (!(id == rhs.id))
      return false;
    if (!(created_at == rhs.created_at))
      return false;
    if (!(active == rhs.active))
      return false;
    if (!(text == rhs.text))
      return false;
    if (!(author_id == rhs.author_id))
      return false;
    if (__isset.author != rhs.__isset.author)
      return false;
    else if (__isset.author && !(author == rhs.author))
      return false;
    if (__isset.n_likes != rhs.__isset.n_likes)
      return false;
    else if (__isset.n_likes && !(n_likes == rhs.n_likes))
      return false;
    return true;
  }
  bool operator != (const TPost &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TPost & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(TPost &a, TPost &b);

std::ostream& operator<<(std::ostream& out, const TPost& obj);


class TLike : public virtual ::apache::thrift::TBase {
 public:

  TLike(const TLike&);
  TLike& operator=(const TLike&);
  TLike() : id(0), created_at(0), account_id(0), post_id(0) {
  }

  virtual ~TLike() noexcept;
  int32_t id;
  int32_t created_at;
  int32_t account_id;
  int32_t post_id;
  TAccount account;
  TPost post;

  void __set_id(const int32_t val);

  void __set_created_at(const int32_t val);

  void __set_account_id(const int32_t val);

  void __set_post_id(const int32_t val);

  void __set_account(const TAccount& val);

  void __set_post(const TPost& val);

  bool operator == (const TLike & rhs) const
  {
    if (!(id == rhs.id))
      return false;
    if (!(created_at == rhs.created_at))
      return false;
    if (!(account_id == rhs.account_id))
      return false;
    if (!(post_id == rhs.post_id))
      return false;
    if (!(account == rhs.account))
      return false;
    if (!(post == rhs.post))
      return false;
    return true;
  }
  bool operator != (const TLike &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TLike & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(TLike &a, TLike &b);

std::ostream& operator<<(std::ostream& out, const TLike& obj);


class TUniquepair : public virtual ::apache::thrift::TBase {
 public:

  TUniquepair(const TUniquepair&);
  TUniquepair& operator=(const TUniquepair&);
  TUniquepair() : id(0), created_at(0), domain(), first_elem(0), second_elem(0) {
  }

  virtual ~TUniquepair() noexcept;
  int32_t id;
  int32_t created_at;
  std::string domain;
  int32_t first_elem;
  int32_t second_elem;

  void __set_id(const int32_t val);

  void __set_created_at(const int32_t val);

  void __set_domain(const std::string& val);

  void __set_first_elem(const int32_t val);

  void __set_second_elem(const int32_t val);

  bool operator == (const TUniquepair & rhs) const
  {
    if (!(id == rhs.id))
      return false;
    if (!(created_at == rhs.created_at))
      return false;
    if (!(domain == rhs.domain))
      return false;
    if (!(first_elem == rhs.first_elem))
      return false;
    if (!(second_elem == rhs.second_elem))
      return false;
    return true;
  }
  bool operator != (const TUniquepair &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TUniquepair & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(TUniquepair &a, TUniquepair &b);

std::ostream& operator<<(std::ostream& out, const TUniquepair& obj);

typedef struct _TUniquepairQuery__isset {
  _TUniquepairQuery__isset() : first_elem(false), second_elem(false) {}
  bool first_elem :1;
  bool second_elem :1;
} _TUniquepairQuery__isset;

class TUniquepairQuery : public virtual ::apache::thrift::TBase {
 public:

  TUniquepairQuery(const TUniquepairQuery&);
  TUniquepairQuery& operator=(const TUniquepairQuery&);
  TUniquepairQuery() : domain(), first_elem(0), second_elem(0) {
  }

  virtual ~TUniquepairQuery() noexcept;
  std::string domain;
  int32_t first_elem;
  int32_t second_elem;

  _TUniquepairQuery__isset __isset;

  void __set_domain(const std::string& val);

  void __set_first_elem(const int32_t val);

  void __set_second_elem(const int32_t val);

  bool operator == (const TUniquepairQuery & rhs) const
  {
    if (!(domain == rhs.domain))
      return false;
    if (__isset.first_elem != rhs.__isset.first_elem)
      return false;
    else if (__isset.first_elem && !(first_elem == rhs.first_elem))
      return false;
    if (__isset.second_elem != rhs.__isset.second_elem)
      return false;
    else if (__isset.second_elem && !(second_elem == rhs.second_elem))
      return false;
    return true;
  }
  bool operator != (const TUniquepairQuery &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TUniquepairQuery & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(TUniquepairQuery &a, TUniquepairQuery &b);

std::ostream& operator<<(std::ostream& out, const TUniquepairQuery& obj);


class TAccountInvalidCredentialsException : public ::apache::thrift::TException {
 public:

  TAccountInvalidCredentialsException(const TAccountInvalidCredentialsException&);
  TAccountInvalidCredentialsException& operator=(const TAccountInvalidCredentialsException&);
  TAccountInvalidCredentialsException() {
  }

  virtual ~TAccountInvalidCredentialsException() noexcept;

  bool operator == (const TAccountInvalidCredentialsException & /* rhs */) const
  {
    return true;
  }
  bool operator != (const TAccountInvalidCredentialsException &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TAccountInvalidCredentialsException & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
  mutable std::string thriftTExceptionMessageHolder_;
  const char* what() const noexcept;
};

void swap(TAccountInvalidCredentialsException &a, TAccountInvalidCredentialsException &b);

std::ostream& operator<<(std::ostream& out, const TAccountInvalidCredentialsException& obj);


class TAccountDeactivatedException : public ::apache::thrift::TException {
 public:

  TAccountDeactivatedException(const TAccountDeactivatedException&);
  TAccountDeactivatedException& operator=(const TAccountDeactivatedException&);
  TAccountDeactivatedException() {
  }

  virtual ~TAccountDeactivatedException() noexcept;

  bool operator == (const TAccountDeactivatedException & /* rhs */) const
  {
    return true;
  }
  bool operator != (const TAccountDeactivatedException &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TAccountDeactivatedException & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
  mutable std::string thriftTExceptionMessageHolder_;
  const char* what() const noexcept;
};

void swap(TAccountDeactivatedException &a, TAccountDeactivatedException &b);

std::ostream& operator<<(std::ostream& out, const TAccountDeactivatedException& obj);


class TAccountInvalidAttributesException : public ::apache::thrift::TException {
 public:

  TAccountInvalidAttributesException(const TAccountInvalidAttributesException&);
  TAccountInvalidAttributesException& operator=(const TAccountInvalidAttributesException&);
  TAccountInvalidAttributesException() {
  }

  virtual ~TAccountInvalidAttributesException() noexcept;

  bool operator == (const TAccountInvalidAttributesException & /* rhs */) const
  {
    return true;
  }
  bool operator != (const TAccountInvalidAttributesException &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TAccountInvalidAttributesException & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
  mutable std::string thriftTExceptionMessageHolder_;
  const char* what() const noexcept;
};

void swap(TAccountInvalidAttributesException &a, TAccountInvalidAttributesException &b);

std::ostream& operator<<(std::ostream& out, const TAccountInvalidAttributesException& obj);


class TAccountUsernameAlreadyExistsException : public ::apache::thrift::TException {
 public:

  TAccountUsernameAlreadyExistsException(const TAccountUsernameAlreadyExistsException&);
  TAccountUsernameAlreadyExistsException& operator=(const TAccountUsernameAlreadyExistsException&);
  TAccountUsernameAlreadyExistsException() {
  }

  virtual ~TAccountUsernameAlreadyExistsException() noexcept;

  bool operator == (const TAccountUsernameAlreadyExistsException & /* rhs */) const
  {
    return true;
  }
  bool operator != (const TAccountUsernameAlreadyExistsException &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TAccountUsernameAlreadyExistsException & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
  mutable std::string thriftTExceptionMessageHolder_;
  const char* what() const noexcept;
};

void swap(TAccountUsernameAlreadyExistsException &a, TAccountUsernameAlreadyExistsException &b);

std::ostream& operator<<(std::ostream& out, const TAccountUsernameAlreadyExistsException& obj);


class TAccountNotFoundException : public ::apache::thrift::TException {
 public:

  TAccountNotFoundException(const TAccountNotFoundException&);
  TAccountNotFoundException& operator=(const TAccountNotFoundException&);
  TAccountNotFoundException() {
  }

  virtual ~TAccountNotFoundException() noexcept;

  bool operator == (const TAccountNotFoundException & /* rhs */) const
  {
    return true;
  }
  bool operator != (const TAccountNotFoundException &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TAccountNotFoundException & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
  mutable std::string thriftTExceptionMessageHolder_;
  const char* what() const noexcept;
};

void swap(TAccountNotFoundException &a, TAccountNotFoundException &b);

std::ostream& operator<<(std::ostream& out, const TAccountNotFoundException& obj);


class TAccountNotAuthorizedException : public ::apache::thrift::TException {
 public:

  TAccountNotAuthorizedException(const TAccountNotAuthorizedException&);
  TAccountNotAuthorizedException& operator=(const TAccountNotAuthorizedException&);
  TAccountNotAuthorizedException() {
  }

  virtual ~TAccountNotAuthorizedException() noexcept;

  bool operator == (const TAccountNotAuthorizedException & /* rhs */) const
  {
    return true;
  }
  bool operator != (const TAccountNotAuthorizedException &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TAccountNotAuthorizedException & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
  mutable std::string thriftTExceptionMessageHolder_;
  const char* what() const noexcept;
};

void swap(TAccountNotAuthorizedException &a, TAccountNotAuthorizedException &b);

std::ostream& operator<<(std::ostream& out, const TAccountNotAuthorizedException& obj);


class TFollowAlreadyExistsException : public ::apache::thrift::TException {
 public:

  TFollowAlreadyExistsException(const TFollowAlreadyExistsException&);
  TFollowAlreadyExistsException& operator=(const TFollowAlreadyExistsException&);
  TFollowAlreadyExistsException() {
  }

  virtual ~TFollowAlreadyExistsException() noexcept;

  bool operator == (const TFollowAlreadyExistsException & /* rhs */) const
  {
    return true;
  }
  bool operator != (const TFollowAlreadyExistsException &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TFollowAlreadyExistsException & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
  mutable std::string thriftTExceptionMessageHolder_;
  const char* what() const noexcept;
};

void swap(TFollowAlreadyExistsException &a, TFollowAlreadyExistsException &b);

std::ostream& operator<<(std::ostream& out, const TFollowAlreadyExistsException& obj);


class TFollowNotFoundException : public ::apache::thrift::TException {
 public:

  TFollowNotFoundException(const TFollowNotFoundException&);
  TFollowNotFoundException& operator=(const TFollowNotFoundException&);
  TFollowNotFoundException() {
  }

  virtual ~TFollowNotFoundException() noexcept;

  bool operator == (const TFollowNotFoundException & /* rhs */) const
  {
    return true;
  }
  bool operator != (const TFollowNotFoundException &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TFollowNotFoundException & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
  mutable std::string thriftTExceptionMessageHolder_;
  const char* what() const noexcept;
};

void swap(TFollowNotFoundException &a, TFollowNotFoundException &b);

std::ostream& operator<<(std::ostream& out, const TFollowNotFoundException& obj);


class TFollowNotAuthorizedException : public ::apache::thrift::TException {
 public:

  TFollowNotAuthorizedException(const TFollowNotAuthorizedException&);
  TFollowNotAuthorizedException& operator=(const TFollowNotAuthorizedException&);
  TFollowNotAuthorizedException() {
  }

  virtual ~TFollowNotAuthorizedException() noexcept;

  bool operator == (const TFollowNotAuthorizedException & /* rhs */) const
  {
    return true;
  }
  bool operator != (const TFollowNotAuthorizedException &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TFollowNotAuthorizedException & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
  mutable std::string thriftTExceptionMessageHolder_;
  const char* what() const noexcept;
};

void swap(TFollowNotAuthorizedException &a, TFollowNotAuthorizedException &b);

std::ostream& operator<<(std::ostream& out, const TFollowNotAuthorizedException& obj);


class TLikeAlreadyExistsException : public ::apache::thrift::TException {
 public:

  TLikeAlreadyExistsException(const TLikeAlreadyExistsException&);
  TLikeAlreadyExistsException& operator=(const TLikeAlreadyExistsException&);
  TLikeAlreadyExistsException() {
  }

  virtual ~TLikeAlreadyExistsException() noexcept;

  bool operator == (const TLikeAlreadyExistsException & /* rhs */) const
  {
    return true;
  }
  bool operator != (const TLikeAlreadyExistsException &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TLikeAlreadyExistsException & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
  mutable std::string thriftTExceptionMessageHolder_;
  const char* what() const noexcept;
};

void swap(TLikeAlreadyExistsException &a, TLikeAlreadyExistsException &b);

std::ostream& operator<<(std::ostream& out, const TLikeAlreadyExistsException& obj);


class TLikeNotFoundException : public ::apache::thrift::TException {
 public:

  TLikeNotFoundException(const TLikeNotFoundException&);
  TLikeNotFoundException& operator=(const TLikeNotFoundException&);
  TLikeNotFoundException() {
  }

  virtual ~TLikeNotFoundException() noexcept;

  bool operator == (const TLikeNotFoundException & /* rhs */) const
  {
    return true;
  }
  bool operator != (const TLikeNotFoundException &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TLikeNotFoundException & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
  mutable std::string thriftTExceptionMessageHolder_;
  const char* what() const noexcept;
};

void swap(TLikeNotFoundException &a, TLikeNotFoundException &b);

std::ostream& operator<<(std::ostream& out, const TLikeNotFoundException& obj);


class TLikeNotAuthorizedException : public ::apache::thrift::TException {
 public:

  TLikeNotAuthorizedException(const TLikeNotAuthorizedException&);
  TLikeNotAuthorizedException& operator=(const TLikeNotAuthorizedException&);
  TLikeNotAuthorizedException() {
  }

  virtual ~TLikeNotAuthorizedException() noexcept;

  bool operator == (const TLikeNotAuthorizedException & /* rhs */) const
  {
    return true;
  }
  bool operator != (const TLikeNotAuthorizedException &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TLikeNotAuthorizedException & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
  mutable std::string thriftTExceptionMessageHolder_;
  const char* what() const noexcept;
};

void swap(TLikeNotAuthorizedException &a, TLikeNotAuthorizedException &b);

std::ostream& operator<<(std::ostream& out, const TLikeNotAuthorizedException& obj);


class TPostInvalidAttributesException : public ::apache::thrift::TException {
 public:

  TPostInvalidAttributesException(const TPostInvalidAttributesException&);
  TPostInvalidAttributesException& operator=(const TPostInvalidAttributesException&);
  TPostInvalidAttributesException() {
  }

  virtual ~TPostInvalidAttributesException() noexcept;

  bool operator == (const TPostInvalidAttributesException & /* rhs */) const
  {
    return true;
  }
  bool operator != (const TPostInvalidAttributesException &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TPostInvalidAttributesException & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
  mutable std::string thriftTExceptionMessageHolder_;
  const char* what() const noexcept;
};

void swap(TPostInvalidAttributesException &a, TPostInvalidAttributesException &b);

std::ostream& operator<<(std::ostream& out, const TPostInvalidAttributesException& obj);


class TPostNotFoundException : public ::apache::thrift::TException {
 public:

  TPostNotFoundException(const TPostNotFoundException&);
  TPostNotFoundException& operator=(const TPostNotFoundException&);
  TPostNotFoundException() {
  }

  virtual ~TPostNotFoundException() noexcept;

  bool operator == (const TPostNotFoundException & /* rhs */) const
  {
    return true;
  }
  bool operator != (const TPostNotFoundException &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TPostNotFoundException & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
  mutable std::string thriftTExceptionMessageHolder_;
  const char* what() const noexcept;
};

void swap(TPostNotFoundException &a, TPostNotFoundException &b);

std::ostream& operator<<(std::ostream& out, const TPostNotFoundException& obj);


class TPostNotAuthorizedException : public ::apache::thrift::TException {
 public:

  TPostNotAuthorizedException(const TPostNotAuthorizedException&);
  TPostNotAuthorizedException& operator=(const TPostNotAuthorizedException&);
  TPostNotAuthorizedException() {
  }

  virtual ~TPostNotAuthorizedException() noexcept;

  bool operator == (const TPostNotAuthorizedException & /* rhs */) const
  {
    return true;
  }
  bool operator != (const TPostNotAuthorizedException &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TPostNotAuthorizedException & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
  mutable std::string thriftTExceptionMessageHolder_;
  const char* what() const noexcept;
};

void swap(TPostNotAuthorizedException &a, TPostNotAuthorizedException &b);

std::ostream& operator<<(std::ostream& out, const TPostNotAuthorizedException& obj);


class TUniquepairNotFoundException : public ::apache::thrift::TException {
 public:

  TUniquepairNotFoundException(const TUniquepairNotFoundException&);
  TUniquepairNotFoundException& operator=(const TUniquepairNotFoundException&);
  TUniquepairNotFoundException() {
  }

  virtual ~TUniquepairNotFoundException() noexcept;

  bool operator == (const TUniquepairNotFoundException & /* rhs */) const
  {
    return true;
  }
  bool operator != (const TUniquepairNotFoundException &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TUniquepairNotFoundException & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
  mutable std::string thriftTExceptionMessageHolder_;
  const char* what() const noexcept;
};

void swap(TUniquepairNotFoundException &a, TUniquepairNotFoundException &b);

std::ostream& operator<<(std::ostream& out, const TUniquepairNotFoundException& obj);


class TUniquepairAlreadyExistsException : public ::apache::thrift::TException {
 public:

  TUniquepairAlreadyExistsException(const TUniquepairAlreadyExistsException&);
  TUniquepairAlreadyExistsException& operator=(const TUniquepairAlreadyExistsException&);
  TUniquepairAlreadyExistsException() {
  }

  virtual ~TUniquepairAlreadyExistsException() noexcept;

  bool operator == (const TUniquepairAlreadyExistsException & /* rhs */) const
  {
    return true;
  }
  bool operator != (const TUniquepairAlreadyExistsException &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TUniquepairAlreadyExistsException & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
  mutable std::string thriftTExceptionMessageHolder_;
  const char* what() const noexcept;
};

void swap(TUniquepairAlreadyExistsException &a, TUniquepairAlreadyExistsException &b);

std::ostream& operator<<(std::ostream& out, const TUniquepairAlreadyExistsException& obj);

} // namespace

#endif
