package com.example.tin.recyler_adapters

import android.support.constraint.ConstraintLayout
import android.support.v7.widget.RecyclerView
import android.view.LayoutInflater
import android.view.ViewGroup
import com.example.tin.R

class NoConsultationsRecyclerAdapter : RecyclerView.Adapter<RecyclerView.ViewHolder>() {
    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): RecyclerView.ViewHolder {
        return NoConsultationsRecyclerViewHolder(
            LayoutInflater.from(parent.context)
                .inflate(R.layout.no_consultations_message_item, parent, false) as ConstraintLayout
        )
    }

    override fun getItemCount(): Int {
        return 1
    }

    override fun onBindViewHolder(holder: RecyclerView.ViewHolder, position: Int) {

    }
}

class NoConsultationsRecyclerViewHolder(item: ConstraintLayout): RecyclerView.ViewHolder(item)