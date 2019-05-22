package com.example.tin.dto.request

class LoginRequest(val login: String,
                   val passwordHash: String,
                   val type: String = "LoginRequest") {


}