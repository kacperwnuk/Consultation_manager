package com.example.tin

import android.annotation.SuppressLint
import android.content.Context
import android.support.constraint.ConstraintLayout
import android.support.v7.widget.RecyclerView
import android.util.Log
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.TextView
import android.widget.Toast
import com.example.tin.data.Consultation
import com.example.tin.data.ConsultationType

class FreeConsultationsRecyclerAdapter(private val consultations: List<Consultation>, private val actionListener: ActionListener): RecyclerView.Adapter<RecyclerView.ViewHolder>() {

    private lateinit var context: Context

    interface ActionListener {
        fun addBefore(day: String, endTime: String)

        fun addAfter(day: String, startTime: String)

        fun reserve()
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): RecyclerView.ViewHolder {
        context = parent.context
        return when (viewType) {
            0 -> {
                StudentSuggestedRecyclerViewHolder(LayoutInflater.from(parent.context)
                    .inflate(R.layout.student_suggested_consultation_item, parent, false) as ConstraintLayout)
            }
            else -> LecturerSuggestedRecyclerViewHolder(LayoutInflater.from(parent.context)
                .inflate(R.layout.free_consultation_item, parent, false) as ConstraintLayout)
        }

    }

    override fun getItemCount(): Int {
        return consultations.size
    }

    @SuppressLint("SetTextI18n")
    override fun onBindViewHolder(holder: RecyclerView.ViewHolder, position: Int) {
        val consultation = consultations[position]
        var endTime = consultation.endTime
        holder.itemView.elevation = 20.0f
        holder.itemView.findViewById<TextView>(R.id.person).text = consultation.person
        holder.itemView.findViewById<TextView>(R.id.day).text = consultation.day
        holder.itemView.setOnTouchListener(object: OnSwipeTouchListener(context) {
            override fun onSwipeRight() {
            }

            override fun onSwipeLeft() {

            }

            override fun onSwipeBottom() {

            }

            override fun onSwipeTop() {
                Toast.makeText(context, "refresh", Toast.LENGTH_LONG).show()
            }
        })
        when (holder) {
            is LecturerSuggestedRecyclerViewHolder -> {

                holder.itemView.findViewById<TextView>(R.id.start_time).text = "${consultation.startTime} - ${consultation.endTime}"
                holder.itemView.findViewById<Button>(R.id.reservation_button).setOnClickListener { v ->
                    Log.d("Adapter", "Clicked $position")
                }
            }
            else -> { //student suggested item
                var i = position + 1
                var j = position
                if (position > 0 && consultations[position - 1].type == ConsultationType.STUDENT_SUGGESTED
                    && consultations[position - 1].person == consultation.person && consultations[position - 1].endTime == consultation.startTime) {
                    holder.itemView.visibility = View.GONE
                    holder.itemView.layoutParams = ViewGroup.LayoutParams(0, 0)
                } else {
                    while (consultations[i].type == ConsultationType.STUDENT_SUGGESTED && i < itemCount) {
                        if (consultations[i].person == consultations[j].person && consultations[i].startTime == consultations[j].endTime) {
                            endTime = consultations[i].endTime
                            i++
                            j++
                        } else {
                            break
                        }
                    }
                }

                holder.itemView.findViewById<TextView>(R.id.start_time).text = "${consultation.startTime} - $endTime"
                holder.itemView.findViewById<Button>(R.id.add_after_button).setOnClickListener {
                    actionListener.addAfter(consultation.day, endTime)
                }
                holder.itemView.findViewById<Button>(R.id.add_before_button).setOnClickListener {
                    actionListener.addBefore(consultation.day, consultation.startTime)
                }
            }
        }
    }

    override fun getItemViewType(position: Int): Int {
        return if (consultations[position].type == ConsultationType.STUDENT_SUGGESTED)
            0
        else
            1
    }

}

class LecturerSuggestedRecyclerViewHolder(item: ConstraintLayout): RecyclerView.ViewHolder(item)
class StudentSuggestedRecyclerViewHolder(item: ConstraintLayout): RecyclerView.ViewHolder(item)


