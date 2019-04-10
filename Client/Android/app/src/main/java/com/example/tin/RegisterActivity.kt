package com.example.tin

import android.animation.Animator
import android.animation.AnimatorListenerAdapter
import android.annotation.TargetApi
import android.os.AsyncTask
import android.os.Build
import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import android.text.TextUtils
import android.view.View
import android.view.inputmethod.EditorInfo
import android.widget.ArrayAdapter
import android.widget.TextView
import kotlinx.android.synthetic.main.activity_register.*

/**
 * A login screen that offers login via email/password.
 */
class RegisterActivity : AppCompatActivity() {

    /**
     * Keep track of the registration task to ensure we can cancel it if requested.
     */
    private var mRegisterTask: UserRegisterTask? = null
    private var lecturers = listOf("L1", "L2", "L3", "L4")

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_register)
        // Set up the login form.
        password.setOnEditorActionListener(TextView.OnEditorActionListener { _, id, _ ->
            if (id == EditorInfo.IME_ACTION_DONE || id == EditorInfo.IME_NULL) {
                attemptRegister()
                return@OnEditorActionListener true
            }
            false
        })

        lecturers_spinner.adapter = ArrayAdapter<String>(this, android.R.layout.simple_spinner_item, lecturers)

        register_button.setOnClickListener { attemptRegister() }
    }

    /**
     * Attempts to sign in or register the account specified by the login form.
     * If there are form errors (invalid email, missing fields, etc.), the
     * errors are presented and no actual login attempt is made.
     */
    private fun attemptRegister() {
        if (mRegisterTask != null) {
            return
        }

        // Reset errors.
        email.error = null
        password.error = null
        name.error = null
        surname.error = null

        // Store values at the time of the login attempt.
        val emailStr = email.text.toString()
        val passwordStr = password.text.toString()
        val nameStr = name.text.toString()
        val surnameStr = surname.text.toString()

        var cancel = false
        var focusView: View? = null

        // Check for a valid password, if the user entered one.// Show a progress spinner, and kick off a background task to
        // perform the user login attempt.
        // There was an error; don't attempt login and focus the first
        // form field with an error.


        if (TextUtils.isEmpty(surnameStr)) {
            surname.error = getString(R.string.error_field_required)
            focusView = surname
            cancel = true
        }
        if (TextUtils.isEmpty(nameStr)) {
            name.error = getString(R.string.error_field_required)
            focusView = name
            cancel = true
        }
        if (TextUtils.isEmpty(passwordStr)) {
            password.error = getString(R.string.error_field_required)
            focusView = password
            cancel = true
        }
        if (TextUtils.isEmpty(emailStr)) {
            email.error = getString(R.string.error_field_required)
            focusView = email
            cancel = true
        }

        if (cancel) {
            // There was an error; don't attempt login and focus the first
            // form field with an error.
            focusView?.requestFocus()
        } else {
            // Show a progress spinner, and kick off a background task to
            // perform the user login attempt.
            showProgress(true)
            val registrationForm =
                RegistrationForm(emailStr, passwordStr, nameStr, surnameStr, lecturers_spinner.selectedItem.toString())
            mRegisterTask = UserRegisterTask(registrationForm)
            mRegisterTask!!.execute(null as Void?)
        }
    }

    /**
     * Shows the progress UI and hides the login form.
     */
    @TargetApi(Build.VERSION_CODES.HONEYCOMB_MR2)
    private fun showProgress(show: Boolean) {
        // On Honeycomb MR2 we have the ViewPropertyAnimator APIs, which allow
        // for very easy animations. If available, use these APIs to fade-in
        // the progress spinner.
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB_MR2) {
            val shortAnimTime = resources.getInteger(android.R.integer.config_shortAnimTime).toLong()

            register_form.visibility = if (show) View.GONE else View.VISIBLE
            register_form.animate()
                .setDuration(shortAnimTime)
                .alpha((if (show) 0 else 1).toFloat())
                .setListener(object : AnimatorListenerAdapter() {
                    override fun onAnimationEnd(animation: Animator) {
                        register_form.visibility = if (show) View.GONE else View.VISIBLE
                    }
                })

            register_progress.visibility = if (show) View.VISIBLE else View.GONE
            register_progress.animate()
                .setDuration(shortAnimTime)
                .alpha((if (show) 1 else 0).toFloat())
                .setListener(object : AnimatorListenerAdapter() {
                    override fun onAnimationEnd(animation: Animator) {
                        register_progress.visibility = if (show) View.VISIBLE else View.GONE
                    }
                })
        } else {
            // The ViewPropertyAnimator APIs are not available, so simply show
            // and hide the relevant UI components.
            register_progress.visibility = if (show) View.VISIBLE else View.GONE
            register_form.visibility = if (show) View.GONE else View.VISIBLE
        }
    }

    /**
     * Represents an asynchronous login/registration task used to authenticate
     * the user.
     */
    inner class UserRegisterTask internal constructor(private val registrationForm: RegistrationForm) :
        AsyncTask<Void, Void, Boolean>() {

        override fun doInBackground(vararg params: Void): Boolean? {
            // TODO: attempt authentication against a network service.

            try {
                // Simulate network access.
                Thread.sleep(2000)
            } catch (e: InterruptedException) {
                return false
            }

            return DUMMY_CREDENTIALS
                .map { it.split(":") }
                .firstOrNull { it[0] == registrationForm.email }
                ?.let {
                    // Account exists, return true if the password matches.
                    it[1] == registrationForm.password
                }
                ?: true
        }

        override fun onPostExecute(success: Boolean?) {
            mRegisterTask = null
            showProgress(false)

            if (success!!) {
                finish()
            } else {
                password.error = getString(R.string.error_incorrect_password)
                password.requestFocus()
            }
        }

        override fun onCancelled() {
            mRegisterTask = null
            showProgress(false)
        }
    }

    companion object {

        /**
         * A dummy authentication store containing known user names and passwords.
         * TODO: remove after connecting to a real authentication system.
         */
        private val DUMMY_CREDENTIALS = arrayOf("foo@example.com:hello", "bar@example.com:world")
    }
}
