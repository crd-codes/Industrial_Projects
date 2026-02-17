package com.crd.edutrack.Controller;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class HealthCheck
{
    @GetMapping("/health")
    public String health()
    {
        return "Application is running";
    }
}