#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>
#include <map>

/**
 * Implements User functionality and information storage
 *  You should not need to derive anything from User at this time
 */
class User{
 public:
  User();
  User(std::string name, int age, double balance, int type, long long password);
  virtual ~User();

  int getAge() const;
  long long getPassword() const;
  double getBalance() const;
  std::string getName() const;
  void deductAmount(double amt);
  virtual void dump(std::ostream& os);
  void setMap(std::map<User*, double> passedIN);
  std::map<User*, double> getMap();

 private:
  std::map<User*, double> individualMap;
  std::string name_;
  int age_;
  double balance_;
  int type_;
  int password_;
};
#endif
