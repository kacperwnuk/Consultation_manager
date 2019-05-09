package com.example.tin.data.entity

class AccountInfo {
    var login: String = ""
    var name: String = ""
    var surname: String = ""

    override fun equals(other: Any?): Boolean {
        val otherAccountInfo = other as AccountInfo
        return otherAccountInfo.login == login
    }
}