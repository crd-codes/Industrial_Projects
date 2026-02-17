# EduTrack (Spring Boot + MongoDB)

## 📌 Project Overview

EduTrack is a software application developed using **Spring Boot** and **MongoDB** to manage batches and students.

The application follows a **layered architecture** (Controller–Service–Repository) to ensure clean code, scalability, and separation of concerns. It exposes REST APIs to perform complete CRUD operations and handles JSON-based client communication.

This project demonstrates:

* Software application development using Spring Boot
* Integration with MongoDB (NoSQL database)
* Layered architecture design
* JSON request and response handling
* HTTP status management
* Backend testing using Postman

---

## 🖥️ Technologies

* Java
* Spring Boot
* Spring Data MongoDB
* MongoDB
* Maven
* Lombok
* Postman

---

## 🚀 Features
* Batch Management
* Create new batch records
* Retrieve all batch details
* Update batch information by ID
* Delete batch records
* Store data in MongoDB collection (`BatchDetails`)
  
* Student Management
* Add students to a batch
* Retrieve students of a specific batch
* Retrieve all students across all batches
* Update student details
* Delete student records
  
* Proper HTTP status handling (200, 201, 204, 404, 400)
* JSON-based API communication
* Clean layered architecture
* Batch Management
---

## 🧠 Concepts Used

* REST Architecture
* Spring Boot Auto Configuration
* Dependency Injection (`@Autowired`)
* MongoDB Document Mapping (`@Document`)
* Repository pattern using `MongoRepository`
* Layered Architecture (Controller–Service–Repository)
* ObjectId handling in MongoDB
* Request/Response handling using `ResponseEntity`
* One-to-many relationship (Batch → Students)
---

## 📂 Project Structure

```
edutrack/
│
├── src/
│   ├── main/
│   │   ├── java/com/crd/edutrack/
│   │   │   ├── Controller/
│   │   │   │   ├── BatchEntryController.java
│   │   │   │   └── StudentEntryController.java
│   │   │   │   └── HealthCheck.java 
│   │   │   ├── Service/
│   │   │   │   ├── BatchEntryService.java
│   │   │   │   └── StudentEntryService.java
│   │   │   ├── Repository/
│   │   │   │   ├── BatchEntryRepository.java
│   │   │   │   └── StudentEntryRepository.java
│   │   │   ├── Entity/
│   │   │   │   ├── BatchEntry.java
│   │   │   │   └── StudentEntry.java
│   │   │   └── EdutrackApplication.java
│   │   └── resources/
│   │       └── application.properties
│
├── pom.xml
└── README.md
```

---

## Requirements to Run This Project

If you download this project from GitHub, make sure your system has the following:

### Required Software

1. **Java (JDK 17 or above)**
   Check:

   ```
   java -version
   ```

2. **Maven**
   Check:

   ```
   mvn -version
   ```

3. **MongoDB Server**
   MongoDB must be installed and running on:

   ```
   mongodb://localhost:27017
   ```

4. **Postman (Optional but Recommended)**
   Used to test the APIs.

---

## How to Run the Project

### Step 1: Download the Project

* Download ZIP from GitHub
  **OR**

```bash
git clone https://github.com/your-username/your-repo-name.git
cd your-repo-name
```

---

### Step 2: Start MongoDB

Make sure MongoDB server is running on your system.

---

### Step 3: Run the Application

```bash
mvn spring-boot:run
```

Application will start at:

```
http://localhost:8080
```

---

## Simple Usage Flow

Install Java + Maven + MongoDB → Start MongoDB → Run Application → Test APIs using Postman

---

## 🔄 Request Flow
```
Client (Postman)
       ↓
Controller (receives JSON)
       ↓
Service (uses BatchEntry  & StudentEntry entities for logic)
       ↓
Repository (maps entities to MongoDB)
       ↓
MongoDB (stores documents)
```
---

## 🖥️ API Usage

### Using Postman (Recommended)

1. Start the Spring Boot application.
2. Open **Postman**.
3. Test the APIs using the following requests:

---
**Batch APIs**

**1. Create Batch**

* Method: `POST`
* URL: `http://localhost:8080/batches`
* Body (JSON):

```json
{
  "name": "Java Batch",
  "fees": 5000
}
```

---

**2. Get All Batches**

* Method: `GET`
* URL: `http://localhost:8080/batches`

---

**3. Update Batch**

* Method: `PUT`
* URL: http://localhost:8080/batches/id/{batchId}
* Body (JSON):

```json
{
  "name": "Advanced Java",
  "fees": 7000
}
```

---

**4. Delete Batch**

* Method: `DELETE`
* URL: http://localhost:8080/batches/id/{batchId}

**Student APIs**

**1. Add Student to a Batch**

* Method: POST
* URL: http://localhost:8080/students
* Body (JSON):
  
```json
{
  "batchId": "{batchId_from_previous_response}",
  "name": "Jay Patil",
  "rollNo": 101
}
```
**2. Get Students by Batch**

* Method: GET
* URL: http://localhost:8080/students/batch/{batchId}
  
**3. Get All Students**

* Method: GET
* URL: http://localhost:8080/students

**4. Update Student**

* Method: PUT
* URL: http://localhost:8080/students/{studentId}
Body (JSON):

```json
{
  "name": "Jay Updated",
  "rollNo": 102
}
```

**5. Delete Student**

* Method: DELETE
* URL: http://localhost:8080/students/{studentId}

---

## 🔮 Future Improvements

* Frontend integration (React)
* Add search/filter APIs for students
* Add authentication & authorization
---

## 👨‍💻 Author

CR Dugade
Aspiring Software Developer

* GitHub: https://github.com/crd-codes
* LinkedIn: https://linkedin.com/in/chakradhar-dugade
* Email : crofficialuse@gmail.com 
