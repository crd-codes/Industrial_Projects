package com.crd.edutrack.Controller;

import com.crd.edutrack.Entity.StudentEntry;
import com.crd.edutrack.Service.StudentEntryService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import java.util.List;

@RestController
@RequestMapping("/students")
public class StudentEntryController {

    @Autowired
    private StudentEntryService studentService;

    // Create Student (http://localhost:8080/students)
    @PostMapping
    public ResponseEntity<StudentEntry> createStudent(@RequestBody StudentEntry student)
    {
        StudentEntry savedStudent = studentService.createStudent(student);
        return ResponseEntity.status(201).body(savedStudent);
    }

    // Get Students all (URL: http://localhost:8080/students/batch/{batchId})
    @GetMapping
    public ResponseEntity<List<StudentEntry>> getAllStudents()
    {
        return ResponseEntity.ok(studentService.getAllStudents());
    }

    // Get Students by Batch (http://localhost:8080/students/batch/{batchId})
    @GetMapping("/batch/{batchId}")
    public ResponseEntity<List<StudentEntry>> getStudentsByBatch(@PathVariable String batchId)
    {
        List<StudentEntry> students = studentService.getStudentsByBatch(batchId);
        return ResponseEntity.ok(students);
    }

    // Update Student ( URL:http://localhost:8080/students/{studentId})
    @PutMapping("/{id}")
    public ResponseEntity<StudentEntry> updateStudent(@PathVariable String id, @RequestBody StudentEntry student)
    {
        StudentEntry updated = studentService.updateStudent(id, student);
        if (updated != null)
            return ResponseEntity.ok(updated);
        else
            return ResponseEntity.notFound().build();
    }

    // Delete Student (URL: http://localhost:8080/students/{studentId})
    @DeleteMapping("/{id}")
    public ResponseEntity<Void> deleteStudent(@PathVariable String id)
    {
        boolean deleted = studentService.deleteStudent(id);
        if (deleted)
            return ResponseEntity.noContent().build();
        else
            return ResponseEntity.notFound().build();
    }
}
