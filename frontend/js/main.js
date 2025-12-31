// --- QueueSmart/js/main.js (COMPLETE UPDATED VERSION) ---

// 1. Backend Configuration
const API_URL = "http://localhost:18080/api"; 

console.log("✅ Main.js is connected and running!");

document.addEventListener("DOMContentLoaded", () => {

    // ---
    // HELPER: Fetch with Authentication Header
    // ---
    async function fetchWithAuth(endpoint, options = {}) {
        const token = localStorage.getItem('sessionToken');
        
        const headers = {
            'Content-Type': 'application/json',
            ...options.headers,
        };

        if (token) {
            headers['Authorization'] = `Bearer ${token}`;
        }

        const response = await fetch(`${API_URL}${endpoint}`, {
            ...options,
            headers: headers
        });
        
        if (response.status === 401) {
            alert("Session expired. Please login again.");
            localStorage.removeItem('sessionToken');
            window.location.href = "/login.html";
            throw new Error("Unauthorized");
        }

        const data = await response.json();
        if (!response.ok) {
            throw new Error(data.message || 'API Error');
        }
        
        return data;
    }

    // ---
    // 1. AUTHENTICATION (Login & Register)
    // ---
    const loginForm = document.getElementById("login-form");
    if (loginForm) {
        loginForm.addEventListener("submit", async (e) => {
            e.preventDefault();
            console.log("Attempting login...");
            
            const emailOrCnic = document.getElementById("email").value;
            const password = document.getElementById("password").value;

            try {
                const response = await fetch(`${API_URL}/login`, {
                    method: 'POST',
                    headers: { 'Content-Type': 'application/json' },
                    body: JSON.stringify({ emailOrCnic, password })
                });

                const data = await response.json();

                if (!response.ok) throw new Error(data.message);

                // Save Session
                localStorage.setItem('sessionToken', data.sessionToken);
                localStorage.setItem('user', JSON.stringify(data.user));

                console.log("Login Success!");
                window.location.href = "dashboard/index.html";

            } catch (error) {
                console.error(error);
                alert("Login Failed: " + error.message);
            }
        });
    }

    const registerForm = document.getElementById("register-form");
    if (registerForm) {
        registerForm.addEventListener("submit", async (e) => {
            e.preventDefault();
            console.log("Attempting registration...");

            const fullName = document.getElementById("full-name").value;
            const cnic = document.getElementById("cnic").value;
            const email = document.getElementById("email").value;
            const password = document.getElementById("password").value;

            try {
                const response = await fetch(`${API_URL}/register`, {
                    method: 'POST',
                    headers: { 'Content-Type': 'application/json' },
                    body: JSON.stringify({ fullName, cnic, email, password })
                });

                const data = await response.json();
                if (!response.ok) throw new Error(data.message);

                alert("Registration successful! Please login.");
                window.location.href = "login.html";

            } catch (error) {
                alert("Registration Failed: " + error.message);
            }
        });
    }

    // ---
    // 2. DASHBOARD & PROFILE DATA
    // ---
    // Update "Welcome back" message
    const dashboardHeader = document.querySelector(".main-header h2");
    if (dashboardHeader) {
        const user = JSON.parse(localStorage.getItem('user'));
        if (user) {
            dashboardHeader.textContent = `Welcome back, ${user.fullName}! 👋`;
        }
    }

    // Fill Profile Page Inputs
    const profileForm = document.getElementById("profile-form");
    if (profileForm) {
        const user = JSON.parse(localStorage.getItem('user'));
        if (user) {
            if(document.getElementById("first-name")) document.getElementById("first-name").value = user.fullName;
            if(document.getElementById("email")) document.getElementById("email").value = user.email;
        }
    }

    // ---
    // 3. BOOKING LOGIC
    // ---
    const bookingForm = document.getElementById("booking-form");
    if (bookingForm) {
        bookingForm.addEventListener("submit", async (e) => {
            e.preventDefault();
            
            const dept = document.getElementById("department").value;
            const branch = document.getElementById("branch").value;
            const category = document.getElementById("category").value;
            const date = document.getElementById("date").value;

            // Combine Dept and Branch to match Backend ID (e.g., NADRA_Gulshan)
            const fullBranchId = `${dept}_${branch}`;

            try {
                const result = await fetchWithAuth("/book", {
                    method: 'POST',
                    body: JSON.stringify({ branch: fullBranchId, category, date })
                });

                console.log("Token booked:", result.token);

                // Save token info to LocalStorage so Payment Page can see it
                localStorage.setItem('pendingPayment', JSON.stringify(result.token));

                // Redirect to Payment Page
                window.location.href = "payment.html"; 

            } catch (error) {
                alert("Booking failed: " + error.message);
            }
        });
    }

    // ---
    // 4. PAYMENT PAGE LOGIC (Updated)
    // ---
    const paymentForm = document.getElementById("payment-form");
    if (paymentForm) {
        // 1. Load the token details
        const pendingToken = JSON.parse(localStorage.getItem('pendingPayment'));
        
        if (pendingToken) {
            // Update HTML elements
            if(document.getElementById("summary-id")) document.getElementById("summary-id").innerText = pendingToken.tokenNumber;
            if(document.getElementById("summary-branch")) document.getElementById("summary-branch").innerText = pendingToken.branchName;
            if(document.getElementById("summary-date")) document.getElementById("summary-date").innerText = pendingToken.bookedTime;
            if(document.getElementById("summary-category")) document.getElementById("summary-category").innerText = pendingToken.category;
        }

        // 2. Handle Pay Button
        paymentForm.addEventListener("submit", (e) => {
            e.preventDefault();
            
            alert("Payment Successful! Your token is confirmed.");
            
            // MOVE Token from 'Pending' to 'Confirmed' for Receipt
            if (pendingToken) {
                localStorage.setItem('confirmedToken', JSON.stringify(pendingToken));
                localStorage.removeItem('pendingPayment');
            }
            
            // Go to Receipt Page (Instead of Queue directly)
            window.location.href = "receipt.html";
        });
    }

    // ---
    // 5. RECEIPT PAGE LOGIC (New)
    // ---
    // We detect if we are on the receipt page by checking for a unique element
    if (document.querySelector(".token-receipt")) {
        const confirmedToken = JSON.parse(localStorage.getItem('confirmedToken'));

        if (confirmedToken) {
            // Fill the Receipt with Real Data
            if(document.getElementById("receipt-number")) document.getElementById("receipt-number").innerText = confirmedToken.tokenNumber;
            if(document.getElementById("receipt-branch")) document.getElementById("receipt-branch").innerText = confirmedToken.branchName;
            if(document.getElementById("receipt-category")) document.getElementById("receipt-category").innerText = confirmedToken.category;
            if(document.getElementById("receipt-date")) document.getElementById("receipt-date").innerText = confirmedToken.bookedTime;
        } else {
            if(document.getElementById("receipt-number")) document.getElementById("receipt-number").innerText = "NO DATA";
        }
    }

    // ---
    // 6. VIEW LIVE QUEUE (Updated Logic)
    // ---
    const queueTable = document.querySelector(".queue-table tbody");
    if (queueTable) {
        async function loadQueue() {
            const dept = document.getElementById("queue-department")?.value || "NADRA";
            const branch = document.getElementById("queue-branch")?.value || "Gulshan";
            const fullBranchId = `${dept}_${branch}`;

            try {
                const list = await fetchWithAuth(`/queue/${fullBranchId}`);
                queueTable.innerHTML = "";

                // Reset Status Box
                if(document.getElementById("status-token")) document.getElementById("status-token").innerText = "--";
                if(document.getElementById("status-position")) document.getElementById("status-position").innerText = "--";
                if(document.getElementById("status-wait")) document.getElementById("status-wait").innerText = "--";
                if(document.getElementById("status-text")) {
                    document.getElementById("status-text").innerText = "Not in Queue";
                    document.getElementById("status-text").className = "status-wait";
                }

                if(list.length === 0) {
                    queueTable.innerHTML = "<tr><td colspan='6'>Queue is empty</td></tr>";
                    return;
                }

                const user = JSON.parse(localStorage.getItem('user'));
                const myUserId = user ? user.userID : -1;

                list.forEach((token, index) => {
                    const isYou = token.userID === myUserId;
                    
                    if (isYou) {
                        // Update Top Status Box
                        if(document.getElementById("status-token")) document.getElementById("status-token").innerText = token.tokenNumber;
                        if(document.getElementById("status-position")) document.getElementById("status-position").innerText = `${index + 1} / ${list.length}`;
                        if(document.getElementById("status-wait")) document.getElementById("status-wait").innerText = `${index * 5} mins`;
                        
                        if(document.getElementById("status-text")) {
                            if (index === 0) {
                                document.getElementById("status-text").innerText = "Your Turn!";
                                document.getElementById("status-text").className = "status-serving";
                            } else {
                                document.getElementById("status-text").innerText = "Waiting";
                                document.getElementById("status-text").className = "status-next";
                            }
                        }
                    }

                    const rowClass = isYou ? "is-you" : "";
                    const row = `
                        <tr class="${rowClass}">
                            <td>${token.tokenNumber} ${isYou ? '<strong>(YOU)</strong>' : ''}</td>
                            <td>${token.category}</td>
                            <td>${token.bookedTime}</td>
                            <td><span class="badge badge-pending">Pending</span></td>
                            <td>${index * 5} min</td>
                        </tr>
                    `;
                    queueTable.innerHTML += row;
                });

            } catch (e) { console.error(e); }
        }

        // Reload when user changes dropdowns
        document.getElementById("queue-department")?.addEventListener("change", loadQueue);
        document.getElementById("queue-branch")?.addEventListener("change", loadQueue);

        // Initial Load
        loadQueue();
        
        // Auto Refresh every 5 seconds
        setInterval(loadQueue, 5000);
    }

    // ---
    // 7. UI LOGIC (Tabs, Sidebar, Time Slots)
    // ---
    
    // Sidebar Active Link
    const currentPage = window.location.pathname.split("/").pop();
    document.querySelectorAll(".sidebar-nav .sidebar-link").forEach(link => {
        const linkPage = link.getAttribute("href").split("/").pop();
        if (linkPage === currentPage) link.classList.add("active");
    });

    // Time Slots Selection
    const timeSlotsContainer = document.querySelector(".time-slots");
    if (timeSlotsContainer) {
        timeSlotsContainer.addEventListener("click", (e) => {
            if (e.target.classList.contains("time-slot")) {
                timeSlotsContainer.querySelectorAll(".time-slot").forEach(s => s.classList.remove("active"));
                e.target.classList.add("active");
            }
        });
    }

    // Payment Tabs
    const paymentTabs = document.querySelectorAll(".payment-tab");
    paymentTabs.forEach(tab => {
        tab.addEventListener("click", () => {
            paymentTabs.forEach(t => t.classList.remove("active"));
            tab.classList.add("active");
            const target = tab.dataset.tab;
            document.querySelectorAll(".payment-tab-content").forEach(c => {
                c.style.display = c.dataset.tabContent === target ? "block" : "none";
            });
        });
    });

    // Profile Tabs
    const profileTabs = document.querySelectorAll(".profile-tab");
    profileTabs.forEach(tab => {
        tab.addEventListener("click", () => {
            profileTabs.forEach(t => t.classList.remove("active"));
            tab.classList.add("active");
            const target = tab.dataset.tab;
            document.querySelectorAll(".profile-tab-content").forEach(c => {
                c.style.display = c.dataset.tabContent === target ? "block" : "none";
            });
        });
    });
});