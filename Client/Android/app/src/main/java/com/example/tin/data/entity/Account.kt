package com.example.tin.data.entity

import com.example.tin.data.entity.enums.AccountRole
import com.example.tin.data.entity.enums.AccountStatus

class Account(
    val id: String,
    val name: String,
    val surname: String,
    val email: String,
    val login: String,
    val hashedPassword: String,
    val role: AccountRole,
    val status: AccountStatus
) {

    constructor(name: String, surname: String, login: String, email: String, password: String) : this("", name, surname, email, login, password, AccountRole.STUDENT, AccountStatus.INACTIVE)
}