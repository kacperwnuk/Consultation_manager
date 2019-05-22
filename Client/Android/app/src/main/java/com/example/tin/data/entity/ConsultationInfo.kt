package com.example.tin.data.entity

import com.example.tin.data.entity.enums.ConsultationType

class ConsultationInfo {

    var _id: String = ""
    var student: AccountInfo = AccountInfo()
    var lecturer: AccountInfo = AccountInfo()
    var consultationDateStart: Long = 0
    var consultationDateEnd: Long = 0
    var room: String = "101"
    var consultationType: ConsultationType = ConsultationType.LECTURER_SUGGESTED
}