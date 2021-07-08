#include "CliRunner.hpp"

#include "ConverterFactory.hpp"

#include <QtDebug>

CliRunner::CliRunner(QStringList &&args) : m_args{ args } {}

void CliRunner::run()
{
    if (m_args.size() < 2) {
        qCritical() << "error, only 1 parameter passed as arg.";
        return;
    }

    const auto input  = m_args.at(0);
    const auto output = m_args.at(1);

    using CF        = ConverterFactory;
    const auto type = CF::fromString(getSuffix(input), getSuffix(output));
    auto converter  = CF::make_converter(type, input, output, ";", "\"", "2.1");

    const auto tmpResult = converter->process();
    qInfo() << tmpResult.success << tmpResult.message
            << tmpResult.detailedMessage;
}

auto CliRunner::getSuffix(const QString &filepath) -> QString
{
    const auto dotPoint = filepath.lastIndexOf('.');
    return filepath.right(filepath.size() - dotPoint);
}