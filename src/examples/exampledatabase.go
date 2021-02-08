package exampledatabase

import (
)

type user struct {
  Id int `gorm:"index;unique"`
  Type_ string `gorm:"column:type"`
  Name string
  Passwd string
}
type Person struct {
  Id int `gorm:"index;unique"`
  Type_ string `gorm:"column:type"`
  Name string
  Age int
  Image bytes.buffer
  ADoubleValue float64
  Sex int
  Mother Person
  Father Person
  Siblings Person
  Children Person
  Roles  []Role
}
type Role struct {
  Id int `gorm:"index;unique"`
  Type_ string `gorm:"column:type"`
  Person Person
}
type Student struct {
  School School
}
type Employee struct {
  Office Office
}
type School struct {
  Id int `gorm:"index;unique"`
  Type_ string `gorm:"column:type"`
  Name string
  Students  []Student
}
type Office struct {
  Id int `gorm:"index;unique"`
  Type_ string `gorm:"column:type"`
  Employees Employee
}
type ThingWithMethods struct {
  Id int `gorm:"index;unique"`
  Type_ string `gorm:"column:type"`
}
