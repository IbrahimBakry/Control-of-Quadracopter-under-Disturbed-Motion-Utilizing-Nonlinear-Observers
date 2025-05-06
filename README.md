# **Disturbance Rejection in Quadrotor Models Using Linear and Nonlinear Observers** 🚁  

## **Summary** 📝  
This research is a Bc.S. graduation project explores a novel approach to rejecting disturbances affecting **Quadrotors** by leveraging **linear and nonlinear observers**. While traditional methods exist, the use of observers for disturbance rejection in Quadrotors remains an underexplored area.  

### **Key Contributions** 🎯  
1. **Model Adaptation**:  
   - Built upon the **OS4 Quadrotor model** from EPFL, modifying it for our control system.  
   - Used **nonlinear dynamic inversion** to simplify PID controller design without linearizing the model.  

2. **Observer Design**:  
   - **Linear Observer**: Provided acceptable performance but had steady-state errors.  
   - **Nonlinear Observer (ESO - Extended State Observer)**: Achieved **excellent results**, eliminating steady-state and observer errors within **1 second** smoothly.
     
![مقارنة خطأ الراصد في الراصد الخطي واللاخطي](https://github.com/user-attachments/assets/ced9770c-7723-4c80-a5b7-b150dce18f16)
![مقارنة خطأ الراصد في حالة وجود الإضطراب وعدم وجوده (حمولة 2g)](https://github.com/user-attachments/assets/3a92bf55-1f80-4573-9ab7-a21eccc6f368)


3. **Disturbance Testing**:  
   - Applied external disturbances (simulating **1.5g and 2g weight increases**).  
   - The system **quickly rejected disturbances**, maintaining stability with minimal performance degradation.  

![مقارنة الإرتفاع في الراصد الخطي واللاخطي](https://github.com/user-attachments/assets/80980f95-0ced-4358-bf76-c8bba45f6589)


4. **Control Strategy**:  
   - Combined **PID control** with **observer-based feedback** for robust performance.  
   - Demonstrated effectiveness in both **simulation and theoretical analysis**.
     
![التحكم بطريقة التغذية العكسية, موضحاً الحلقتين الداخلية والخارجية](https://github.com/user-attachments/assets/4fc80783-4df8-4f53-ba00-8e76e850ec87)

### **Key Features** ✨  
- **Disturbance Rejection Control (DRC)**: Effectively handles external disruptions.  
- **Nonlinear Dynamics**: Maintains accuracy without oversimplification.  
- **Real-World Applicability**: Suitable for **indoor UAV applications** (future work may extend to outdoor).  

### **Final Thoughts** 💡  
This work presents a **practical and efficient** method for Quadrotor disturbance rejection using observers. The **nonlinear ESO-based approach** outperforms linear methods, making it ideal for **real-world UAV stability**. Future expansions could bridge the gap to **autonomous outdoor flight**.  

🚀 **Keywords**: Quadrotor, Linear Observers, Nonlinear Observers, PID Control, Disturbance Rejection (DRC).  
