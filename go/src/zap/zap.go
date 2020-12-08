package main

import (
	"go.uber.org/zap"
	"time"
	"log"
)

func NewLogger() (*zap.Logger, error) {
	//see the difference between these Config
	//cfg := zap.NewProductionConfig()
	cfg := zap.NewDevelopmentConfig()
	
	cfg.OutputPaths = []string {
		"./test.log",
		"stderr",
	}
	return cfg.Build()
}

func main () {
	logger,err := NewLogger()
	if err != nil {
		log.Fatalf (err.Error())
	}
	defer logger.Sync()

	sugar := logger.Sugar()

	const url = "http://example.com"

	sugar.Infow ("Failed to fetch URL.", 
		// Structured context as loosely typed KV pairs.
		"url", url,
		"attempt", 3,
		"backoff", time.Second,
	)
	sugar.Infof ("Failed to fetch URL: %s", url)

	// In the unusual situations where every microsecond matters, use the
	// Logger. It's even faster than the SugaredLogger, but only supports
	// structured logging.
	logger.Info("Failed to fetch URL.",
		// Structured context as strongly typed fields.
		zap.String("url", url),
		zap.Int("attempt", 3),
		zap.Duration("backoff", time.Second),
	)
}
