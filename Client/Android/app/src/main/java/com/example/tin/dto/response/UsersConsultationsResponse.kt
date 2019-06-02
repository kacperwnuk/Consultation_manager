package com.example.tin.dto.response

import com.fasterxml.jackson.annotation.JsonIgnoreProperties

@JsonIgnoreProperties("type")
class UsersConsultationsResponse {
    var status = -1
}