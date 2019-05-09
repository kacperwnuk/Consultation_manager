package com.example.tin.dto.request

class RegisterRequest(
    val email: String,
    val login: String,
    val password: String,
    val name: String,
    val surname: String,
    val accountRole: Int = 2,
    val type: Int = 3
) {
}