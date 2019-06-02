package com.example.tin

import android.animation.Animator
import android.animation.AnimatorListenerAdapter
import android.annotation.TargetApi
import android.content.Intent
import android.os.AsyncTask
import android.os.Build
import android.os.Bundle
import android.os.Handler
import android.support.v7.app.AppCompatActivity
import android.text.TextUtils
import android.view.View
import android.view.inputmethod.EditorInfo
import android.widget.TextView
import com.example.tin.data.CredentialsManager
import com.example.tin.data.DataService
import com.google.android.gms.auth.api.credentials.Credential
import kotlinx.android.synthetic.main.activity_login.*


/**
 * A login screen that offers login via email/password.
 */
class LoginActivity : AppCompatActivity(), CredentialsManager.RetrieveCredentialsListener, DataService.LoginListener {

    private val handler = Handler()
    private var progressing = false

    init {
        DataService.setLoginListener(this)
    }

    override fun onLoginSuccess() {
        handler.post {
            showProgress(false)
            val mainActivityIntent = Intent(applicationContext, MainActivity::class.java)
            mainActivityIntent.putExtra("Credential", credential)
            mainActivityIntent.flags = Intent.FLAG_ACTIVITY_CLEAR_TOP
            startActivity(mainActivityIntent)
            finish()
        }
    }

    override fun onLoginFailure(errorMessage: String) {
        handler.post {
            showProgress(false)
            password.error = errorMessage
            password.requestFocus()
        }
    }

    override fun onBackPressed() {
        if (progressing) {
            showProgress(false)
        } else {
            super.onBackPressed()
        }
    }

    /**
     * Keep track of the login task to ensure we can cancel it if requested.
     */
    private var mAuthTask: UserLoginTask? = null
    private var credential: Credential? = null
    private lateinit var credentialsManager: CredentialsManager

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_login)
        credentialsManager = CredentialsManager(this)

        // Set up the login form.
        password.setOnEditorActionListener(TextView.OnEditorActionListener { _, id, _ ->
            if (id == EditorInfo.IME_ACTION_DONE || id == EditorInfo.IME_NULL) {
                attemptLogin()
                return@OnEditorActionListener true
            }
            false
        })
        credentialsManager.attemptAutoLogin()
        email_sign_in_button.setOnClickListener { attemptLogin() }
        go_to_register_button.setOnClickListener { startActivity(Intent(this, RegisterActivity::class.java)) }
    }


    override fun login(credential: Credential) {
        this.credential = credential
        showProgress(true)
        mAuthTask = UserLoginTask(credential.id, credential.password!!)
        mAuthTask!!.execute(null as Void?)
    }


    /**
     * Attempts to sign in or register the account specified by the login form.
     * If there are form errors (invalid email, missing fields, etc.), the
     * errors are presented and no actual login attempt is made.
     */
    private fun attemptLogin() {
        if (mAuthTask != null) {
            return
        }

        // Reset errors.
        login.error = null
        password.error = null

        // Store values at the time of the login attempt.
        val loginStr = login.text.toString()
        val passwordStr = password.text.toString()

        var cancel = false
        var focusView: View? = null

        // Check for a password
        if (TextUtils.isEmpty(passwordStr)) {
            password.error = getString(R.string.error_field_required)
            focusView = password
            cancel = true
        }

        // Check for a login
        if (TextUtils.isEmpty(loginStr)) {
            login.error = getString(R.string.error_field_required)
            focusView = login
            cancel = true
        }

        if (cancel) {
            // There was an error; don't attempt login and focus the first
            // form field with an error.
            focusView?.requestFocus()
        } else {
            // Show a progress spinner, and kick off a background task to
            // perform the user login attempt.
            this.credential = Credential.Builder(loginStr)
                .setPassword(passwordStr)
                .build()
            showProgress(true)
            mAuthTask = UserLoginTask(loginStr, passwordStr)
            mAuthTask!!.execute(null as Void?)
        }
    }

    /**
     * Shows the progress UI and hides the login form.
     */
    @TargetApi(Build.VERSION_CODES.HONEYCOMB_MR2)
    private fun showProgress(show: Boolean) {
        progressing = show
        // On Honeycomb MR2 we have the ViewPropertyAnimator APIs, which allow
        // for very easy animations. If available, use these APIs to fade-in
        // the progress spinner.
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB_MR2) {
            val shortAnimTime = resources.getInteger(android.R.integer.config_shortAnimTime).toLong()

            email_login_form.visibility = if (show) View.GONE else View.VISIBLE
            email_login_form.animate()
                .setDuration(shortAnimTime)
                .alpha((if (show) 0 else 1).toFloat())
                .setListener(object : AnimatorListenerAdapter() {
                    override fun onAnimationEnd(animation: Animator) {
                        login_form.visibility = if (show) View.GONE else View.VISIBLE
                    }
                })

            login_progress.visibility = if (show) View.VISIBLE else View.GONE
            login_progress.animate()
                .setDuration(shortAnimTime)
                .alpha((if (show) 1 else 0).toFloat())
                .setListener(object : AnimatorListenerAdapter() {
                    override fun onAnimationEnd(animation: Animator) {
                        login_progress.visibility = if (show) View.VISIBLE else View.GONE
                    }
                })
        } else {
            // The ViewPropertyAnimator APIs are not available, so simply show
            // and hide the relevant UI components.
            login_progress.visibility = if (show) View.VISIBLE else View.GONE
            email_login_form.visibility = if (show) View.GONE else View.VISIBLE
        }
    }



    /**
     * Represents an asynchronous login/registration task used to authenticate
     * the user.
     */
    inner class UserLoginTask internal constructor(private val mEmail: String, private val mPassword: String) :
        AsyncTask<Void, Void, Boolean>() {

        override fun doInBackground(vararg params: Void): Boolean? {
            // TODO: attempt authentication against a network service.

            try {
                DataService.login(mEmail, mPassword)
            } catch (e: InterruptedException) {
                return false
            }

            credentialsManager.saveCredentials(mEmail, mPassword)

            return DUMMY_CREDENTIALS
                .map { it.split(":") }
                .firstOrNull { it[0] == mEmail }
                ?.let {
                    // Account exists, return true if the password matches.
                    it[1] == mPassword
                }
                ?: true
        }

        override fun onPostExecute(success: Boolean?) {
            mAuthTask = null

            if (success!!) {

            } else {
                password.error = getString(R.string.error_incorrect_password)
                password.requestFocus()
            }
        }

        override fun onCancelled() {
            mAuthTask = null
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
