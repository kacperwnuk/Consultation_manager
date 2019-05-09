package com.example.tin.dto.request

class RegisterRequest(
    val username: String,
    val password: String,
    val name: String,
    val surnname: String,
    val type: Int = 2
) {
}