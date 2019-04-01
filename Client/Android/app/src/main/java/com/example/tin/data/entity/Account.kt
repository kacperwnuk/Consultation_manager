package com.example.tin.data.entity

import com.example.tin.data.entity.enums.AccountRole
import com.example.tin.data.entity.enums.AccountStatus

class Account(
    val id: Long,
    val name: String,
    val surname: String,
    val email: String,
    val login: String,
    val hashedPassword: String,
    val role: AccountRole,
    val status: AccountStatus
) {
}